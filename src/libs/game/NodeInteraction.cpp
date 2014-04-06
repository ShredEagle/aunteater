#include "NodeInteraction.h"

#include "ComponentInteraction.h"
#include <typeinfo>

const std::set<const std::type_info *> NodeInteraction::gComponentTypes{ &typeid(ComponentInteraction) };