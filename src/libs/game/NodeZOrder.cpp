#include "NodeZOrder.h"

#include "ComponentZord.h"
#include "ComponentPosition.h"
#include "ComponentZReorderable.h"
#include <typeinfo>

const std::set<const std::type_info *> NodeZOrder::gComponentTypes{ &typeid(ComponentZord), &typeid(ComponentPosition), &typeid(ComponentZReorderable) };