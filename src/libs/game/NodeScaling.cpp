#include "NodeScaling.h"

#include "ComponentSprite.h"
#include "ComponentPosition.h"
#include "ComponentScale.h"
#include <typeinfo>

const std::set<const std::type_info *> NodeScaling::gComponentTypes{ &typeid(ComponentScale), &typeid(ComponentSprite), &typeid(ComponentPosition) };