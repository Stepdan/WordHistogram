#include <QFileDialog>
#include <QStandardPaths>

#include "Proc/ProcessManager/ProcessManager.h"

#include "UI/Drawer/DrawerFactory.h"

#include "Mediator.h"

#include <QDebug>

struct Mediator::Impl
{
    std::unique_ptr<Proc::ProcessManager> processManager;
    std::unique_ptr<Interfaces::IDrawer> m_drawer;
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

    m_impl->m_drawer = CreateDrawer(DrawerType::Drawer, m_mainWindow->GetScene());

    connect(m_mainWindow.get(), &MainWindow::loadFile, this, &Mediator::OnLoad );
    connect(m_mainWindow.get(), &MainWindow::start   , this, &Mediator::OnStart);
}

//.....................................................................................

Mediator::~Mediator() = default;

//.....................................................................................

void Mediator::OnLoad()
{
    m_impl->processManager->Stop();

    const auto path = QFileDialog::getOpenFileName(m_mainWindow.get(), "Open file", QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).front(), "Text Files (*.txt)");

    if(path.isEmpty())
        return;

    m_impl->processManager->SetOpenPath(path);
    m_mainWindow->SetStartEnabled(true);
    m_mainWindow->Clear();
}

//.....................................................................................

void Mediator::OnStart()
{
    m_impl->processManager->Start();
    m_mainWindow->SetStartEnabled(false);
}

//.....................................................................................

void Mediator::ProcessData(Items&& items)
{
    auto sortedItems = std::move(items);
    std::sort(sortedItems.begin(), sortedItems.end());

    m_impl->m_drawer->Draw(sortedItems);
    m_mainWindow->UpdateData(sortedItems);
}

//.....................................................................................

void Mediator::ProcessProgress(size_t value, bool isMax)
{
    m_mainWindow->UpdateProgress(value, isMax);
}
