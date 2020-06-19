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

    connect(m_impl->ui.loadButton, &QAbstractButton::clicked, this, &MainWindow::loadFile);
}

//.....................................................................................

MainWindow::~MainWindow() = default;
