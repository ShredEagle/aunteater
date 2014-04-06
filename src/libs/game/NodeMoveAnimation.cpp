#include "NodeMoveAnimation.h"

#include "ComponentSpeed.h"
#include "ComponentAnimationState.h"
#include <typeinfo>

const std::set<const std::type_info *> NodeMoveAnimation::gComponentTypes{ &typeid(ComponentSpeed), &typeid(ComponentAnimationState) };