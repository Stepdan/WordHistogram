#include "Drawer.h"

#include "DrawerFactory.h"

std::unique_ptr<Interfaces::IDrawer> CreateDrawer(DrawerType type, QGraphicsScene* scene)
{
    switch(type)
    {
    case DrawerType::Drawer:
        return std::make_unique<Drawer>(scene);
    default:
        return nullptr;
    }
}
