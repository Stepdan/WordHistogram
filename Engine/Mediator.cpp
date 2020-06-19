#include "Mediator.h"

//.....................................................................................

namespace WordHistogram
{

class Mediator::Impl
{

};

//.....................................................................................

Mediator::Mediator(const std::shared_ptr<MainWindow>& mainWindow)
    : m_mainWindow(mainWindow)
    , m_impl(std::make_unique<Impl>())
{
    connect(m_mainWindow.get(), &MainWindow::loadFile, this, &Mediator::OnLoad);
}

//.....................................................................................

Mediator::~Mediator() = default;

//.....................................................................................

void Mediator::OnLoad()
{

}

}
