#pragma once

#include <memory>

#include <QGraphicsView>

class Scene
    : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Scene(QWidget *parent = nullptr);
    ~Scene();

protected:
    void wheelEvent(QWheelEvent* event) override;

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};
