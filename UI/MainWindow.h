#pragma once

#include <memory>

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void loadFile();

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
