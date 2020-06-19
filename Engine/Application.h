#pragma once

#include <QApplication>

class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int& argc, char** argv);

    void SetStyle();
};

/**
* @brief Получение указателя на синглтон Application
**/

#define projectApp (static_cast<Application*>(QApplication::instance()))
