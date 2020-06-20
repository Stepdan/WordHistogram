#pragma once

#include <memory>

#include <QMainWindow>

#include "Proc/Interfaces/IHistogram.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void loadFile();
    void start();

private slots:
    void OnDataUpdated(const Items&);

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
