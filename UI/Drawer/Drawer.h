#pragma once

#include <QGraphicsScene>

#include "Proc/Interfaces/IHistogram.h"

#include "UI/Interfaces/IDrawer.h"

class Drawer : public Interfaces::IDrawer
{
public:
    explicit Drawer(QGraphicsScene* scene);
    ~Drawer();

public:
    void Draw(const Items& items) override;

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};
