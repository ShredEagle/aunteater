#include "NodePlayerCollision.h"

#include "ComponentPosition.h"
#include "ComponentPlayer.h"
#include <typeinfo>

const std::set<const std::type_info *> NodePlayerCollision::gComponentTypes{ &typeid(ComponentPosition), &typeid(ComponentPlayer) };