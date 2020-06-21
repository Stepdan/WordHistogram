#pragma once

#include <memory>

#include <QGraphicsScene>

#include "UI/Interfaces/IDrawer.h"

#include "DrawerType.h"

std::unique_ptr<Interfaces::IDrawer> CreateDrawer(DrawerType, QGraphicsScene*);
