#pragma once

#include <memory>

#include "UI/MainWindow.h"

class Mediator : public QObject
{
    Q_OBJECT

public:
    Mediator(const std::shared_ptr<MainWindow>& mainWindow);
    ~Mediator();

private slots:
    void OnLoad();
    void OnStart();

private:
    void ProcessData(Items&&);
    void ProcessProgress(size_t, bool);

private:
    std::shared_ptr<MainWindow> m_mainWindow;

    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
