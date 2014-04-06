#include "NodeControl.h"

#include "ComponentKeyboard.h"
#include "ComponentSpeed.h"
#include <typeinfo>

const std::set<const std::type_info *> NodeControl::gComponentTypes { &typeid(ComponentKeyboard), &typeid(ComponentSpeed) };