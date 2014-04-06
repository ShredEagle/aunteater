#include "NodeAnimation.h"

#include "ComponentSprite.h"
#include "ComponentAnimationState.h"
#include <typeinfo>

const std::set<const std::type_info *> NodeAnimation::gComponentTypes{ &typeid(ComponentSprite), &typeid(ComponentAnimationState) };