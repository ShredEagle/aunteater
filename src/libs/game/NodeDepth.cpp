#include "NodeDepth.h"

#include "ComponentSprite.h"
#include "ComponentPosition.h"
#include <typeinfo>

const std::set<const std::type_info *> NodeDepth::gComponentTypes{ &typeid(ComponentSprite), &typeid(ComponentPosition) };