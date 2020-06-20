#include <QFileDialog>
#include <QStandardPaths>

#include "Proc/ProcessManager/ProcessManager.h"

#include "Mediator.h"

struct Mediator::Impl
{
    std::unique_ptr<Proc::ProcessManager> processManager;
};

//.....................................................................................

Mediator::Mediator(const std::shared_ptr<MainWindow>& mainWindow)
    : m_mainWindow(mainWindow)
    , m_impl(std::make_unique<Impl>())
{
    Proc::ProcessManager::Initializer initializer;
    initializer.dataCallback = std::bind(&Mediator::ProcessData, this, std::placeholders::_1);
    initializer.progressCallback = std::bind(&Mediator::ProcessProgress, this, std::placeholders::_1, std::placeholders::_2);
    m_impl->processManager = std::make_unique<Proc::ProcessManager>(std::move(initializer));

    connect(m_mainWindow.get(), &MainWindow::loadFile   , this, &Mediator::OnLoad   );
    connect(m_mainWindow.get(), &MainWindow::start      , this, &Mediator::OnStart  );
}

//.....................................................................................

Mediator::~Mediator() = default;

//.....................................................................................

void Mediator::OnLoad()
{
    const auto path = QFileDialog::getOpenFileName(m_mainWindow.get(), "Open file", QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).front(), "Text Files (*.txt)");

    if(path.isEmpty())
        return;

    m_impl->processManager->SetOpenPath(path);
}

//.....................................................................................

void Mediator::OnStart()
{
    m_impl->processManager->Start();
}

//.....................................................................................

void Mediator::ProcessData(Items&& items)
{

}

//.....................................................................................

void Mediator::ProcessProgress(size_t value, bool isMax)
{

}
