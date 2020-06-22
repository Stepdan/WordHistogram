#include <atomic>
#include <condition_variable>
#include <future>
#include <mutex>
#include <queue>
#include <thread>

#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#include "Util/FileUtils.h"
#include "Util/Forwarder.h"

#include "Proc/Histogram/Histogram.h"

#include "ProcessManager.h"

namespace
{

// Я ни в коем разе не джедай регулярок, сей грамоте не обучен, поэтому так:
const QRegExp REG_EXP = QRegExp("\\W+");

constexpr size_t INVALID_VALUE = -1;

}

namespace Proc
{

class ProcessManager::Impl
{
public:
    Impl(Initializer&& initializer)
        : m_dataCallback(std::move(initializer.dataCallback))
        , m_progressCallback(std::move(initializer.progressCallback))
        , m_histogram(std::make_unique<Histogram>())
    {}

    ~Impl()
    {
        Stop();
    }

public:
    void SetOpenPath(const QString& path)
    {
        m_path = path;
    }

    void Start()
    {
        if(!Util::CheckFile(m_path))
            return; // @todo Показать сообщение

        m_inProgress = true;
        m_needUpdateHistogram = false;
        m_histogram->Clear();

        std::promise<void>().swap(m_readerThreadStartedPromise);
        m_readerThread = std::thread(&ProcessManager::Impl::ReaderFunction, this);
        {
            auto waitForReaderStart = m_readerThreadStartedPromise.get_future();
            waitForReaderStart.get();
        }

        std::promise<void>().swap(m_histogramThreadStartedPromise);
        m_histogramThread = std::thread(&ProcessManager::Impl::HistogramFunction, this);
        {
            auto waitForHistogramStart = m_histogramThreadStartedPromise.get_future();
            waitForHistogramStart.get();
        }
    }

    void Stop()
    {
        if(!m_inProgress)
            return;

        m_inProgress = false;
        m_needUpdateHistogram = false;

        m_progressCondition.notify_all();

        if(m_readerThread.joinable())
            m_readerThread.join();

        if(m_histogramThread.joinable())
            m_histogramThread.join();
    }

private:
    void ReaderFunction()
    {
        m_readerThreadStartedPromise.set_value();

        QFile file(m_path);
        file.open(QFile::ReadOnly | QIODevice::Text);

        const auto fileSize = file.size();
        m_forwarder.Forward([this, size = fileSize](){ m_progressCallback(size, true); });

        size_t oldPercent = INVALID_VALUE;

        while(m_inProgress && !file.atEnd())
        {
            const auto lineStr = QString::fromUtf8(file.readLine());
            if(lineStr.isEmpty())
                continue;

            auto list = lineStr.split(REG_EXP, QString::SplitBehavior::SkipEmptyParts);
            {
                std::unique_lock<std::mutex> lock(m_progressMutex);
                m_queue.push(std::move(list));
            }

            const auto size = fileSize - static_cast<size_t>(file.bytesAvailable());
            if(auto curValue(100 * size / fileSize); oldPercent == INVALID_VALUE || oldPercent < curValue)
            {
                m_forwarder.Forward([this, value = size](){ m_progressCallback(value, false); });
                oldPercent = curValue;
                m_needUpdateHistogram = true;
            }

            m_progressCondition.notify_all();
        }
    }

    void HistogramFunction()
    {
        m_histogramThreadStartedPromise.set_value();

        while(m_inProgress)
        {
            std::unique_lock<std::mutex> lock(m_progressMutex);
            m_progressCondition.wait(lock, [this](){ return !m_queue.empty() || !m_inProgress; });
            while(!m_queue.empty())
            {
                m_histogram->AddItems(m_queue.front());
                m_queue.pop();
            }
            if(m_needUpdateHistogram)
            {
                m_forwarder.Forward([this](){ m_dataCallback(m_histogram->GetItems()); });
                m_needUpdateHistogram = false;
            }
        }

        m_forwarder.Forward([this](){ m_dataCallback(m_histogram->GetItems()); });
    }

private:
    std::atomic_bool m_inProgress;
    std::mutex m_progressMutex;
    std::condition_variable m_progressCondition;

    std::atomic_bool m_needUpdateHistogram;

    std::thread m_readerThread, m_histogramThread;
    std::promise<void> m_readerThreadStartedPromise, m_histogramThreadStartedPromise;

    const Util::Forwarder m_forwarder;

    std::queue<QStringList> m_queue;

private:
    DataCallbackType m_dataCallback;
    ProgressCallbackType m_progressCallback;
    std::unique_ptr<Interfaces::IHistogram> m_histogram;
    QString m_path;
};

//.....................................................................................

ProcessManager::ProcessManager(Initializer&& initializer)
    : m_impl(std::make_unique<Impl>(std::move(initializer)))
{}

//.....................................................................................

ProcessManager::~ProcessManager() = default;

//.....................................................................................

void ProcessManager::SetOpenPath(const QString& path)
{
    m_impl->SetOpenPath(path);
}

//.....................................................................................

void ProcessManager::Start()
{
    m_impl->Start();
}

//.....................................................................................

void ProcessManager::Stop()
{
    m_impl->Stop();
}

}
