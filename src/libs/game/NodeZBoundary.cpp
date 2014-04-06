#include "NodeZBoundary.h"

#include "ComponentZBoundary.h"
#include <typeinfo>

const std::set<const std::type_info *> NodeZBoundary::gComponentTypes{ &typeid(ComponentZBoundary) };