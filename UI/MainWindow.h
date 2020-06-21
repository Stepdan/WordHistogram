#pragma once

#include <memory>

#include <QGraphicsScene>
#include <QMainWindow>

#include "Proc/Interfaces/IHistogram.h"

#include "UI/Interfaces/IDrawer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void SetStartEnabled(bool);
    void UpdateData(const Items&);

public:
    QGraphicsScene* GetScene() const;

signals:
    void loadFile();
    void start();

private slots:
    void OnLoadFile();

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
