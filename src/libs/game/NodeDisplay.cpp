#include "NodeDisplay.h"

#include "ComponentSprite.h"
#include "ComponentPosition.h"
#include <typeinfo>

const std::set<const std::type_info *> NodeDisplay::gComponentTypes{ &typeid(ComponentSprite), &typeid(ComponentPosition) };