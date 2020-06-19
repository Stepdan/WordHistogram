#pragma once

#include <functional>

#include <QObject>

namespace Utils
{

class Forwarder : public QObject
{
    Q_OBJECT

public:
    using FunctorType = std::function<void ()>;

    Forwarder();

    void Forward(FunctorType f) const;

signals:
    void ExecuteFunctor(FunctorType f) const;

private slots:
    void OnExecuteFunctor(FunctorType f);
};

}
