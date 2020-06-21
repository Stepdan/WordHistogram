#include "UI/LegendModel/DeclareMetatype.h"
#include "UI/LegendModel/LegendModel.h"
#include "UI/LegendModel/LegendModelRoles.h"
#include "UI/LegendModel/Delegate/LegendModelDelegate.h"


#include "MainWindow.h"
#include "ui_MainWindow.h"

struct MainWindow::Impl
{
    Impl()
        : ui(Ui::MainWindow())
    {}

    Ui::MainWindow ui;

    QAbstractListModel* legendModel;
};

//.....................................................................................

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_impl(std::make_unique<Impl>())
{
    m_impl->ui.setupUi(this);

    m_impl->legendModel = new LegendModel(this);
    m_impl->ui.legendView->setModel(m_impl->legendModel);
    m_impl->ui.legendView->setItemDelegate(new LegendModelDelegate(m_impl->ui.legendView));

    connect(m_impl->ui.startButton, &QAbstractButton::clicked, this, &MainWindow::start     );
    connect(m_impl->ui.loadButton , &QAbstractButton::clicked, this, &MainWindow::OnLoadFile);

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

void MainWindow::UpdateData(const Items& items)
{
    m_impl->legendModel->setData(QModelIndex(), QVariant::fromValue(items), static_cast<int>(LegendModelRoles::Items));
}

//.....................................................................................

void MainWindow::UpdateProgress(size_t value, bool isMax)
{
    if(isMax)
        m_impl->ui.progressBar->setMaximum(value);
    else
        m_impl->ui.progressBar->setValue(value);
}

//.....................................................................................

QGraphicsScene* MainWindow::GetScene() const
{
    return m_impl->ui.graphicsView->scene();
}

//.....................................................................................

void MainWindow::OnLoadFile()
{
    UpdateProgress(0);
    SetStartEnabled(false);
    m_impl->ui.graphicsView->scene()->clear();
    m_impl->legendModel->setData(QModelIndex(), QVariant::fromValue(Items()), static_cast<int>(LegendModelRoles::Items));

    emit loadFile();
}
