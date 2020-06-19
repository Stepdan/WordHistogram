#pragma once

#include <memory>

#include "UI/MainWindow.h"

namespace WordHistogram
{

class Mediator : public QObject
{
    Q_OBJECT

public:
    Mediator(const std::shared_ptr<MainWindow>& mainWindow);
    ~Mediator();

private slots:
    void OnLoad();

private:
    std::shared_ptr<MainWindow> m_mainWindow;

    class Impl;
    std::unique_ptr<Impl> m_impl;
};

}
