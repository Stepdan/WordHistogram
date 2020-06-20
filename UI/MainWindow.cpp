#include "MainWindow.h"
#include "ui_MainWindow.h"

struct MainWindow::Impl
{
    Impl()
        : ui(Ui::MainWindow())
    {}

    Ui::MainWindow ui;
};

//.....................................................................................

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_impl(std::make_unique<Impl>())
{
    m_impl->ui.setupUi(this);

    connect(m_impl->ui.startButton  , &QAbstractButton::clicked, this, &MainWindow::start   );

    connect(m_impl->ui.loadButton   , &QAbstractButton::clicked, this, &MainWindow::OnLoadFile);

    SetStartEnabled(false);
}

//.....................................................................................

MainWindow::~MainWindow() = default;

//.....................................................................................

void MainWindow::SetStartEnabled(bool enabled)
{
    m_impl->ui.startButton->setEnabled(enabled);
}

//.....................................................................................

void MainWindow::OnLoadFile()
{
    SetStartEnabled(false);
    emit loadFile();
}

//.....................................................................................

void MainWindow::OnDataUpdated(const Items& items)
{

}
