#include "NodeBarrier.h"

#include "ComponentBarrier.h"
#include <typeinfo>

const std::set<const std::type_info *> NodeBarrier::gComponentTypes{ &typeid(ComponentBarrier) };