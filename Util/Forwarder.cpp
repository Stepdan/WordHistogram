#include <cassert>

#include <QtCore>

#include "Forwarder.h"

namespace Utils {

Forwarder::Forwarder()
{
    qRegisterMetaType<FunctorType>("FunctorType");

    bool result = connect(this, SIGNAL(ExecuteFunctor(FunctorType)), this, SLOT(OnExecuteFunctor(FunctorType)), Qt::QueuedConnection);
    if (!result)
        assert(!"Failed to connect signal and slot");
}

void Forwarder::Forward(Forwarder::FunctorType f) const
{
    emit ExecuteFunctor(f);
}

void Forwarder::OnExecuteFunctor(Forwarder::FunctorType f)
{
    f();
}

}
