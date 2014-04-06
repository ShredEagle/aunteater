#include "NodeMove.h"

#include "ComponentSpeed.h"
#include "ComponentPosition.h"
#include <typeinfo>

const std::set<const std::type_info *> NodeMove::gComponentTypes{ &typeid(ComponentSpeed), &typeid(ComponentPosition) };