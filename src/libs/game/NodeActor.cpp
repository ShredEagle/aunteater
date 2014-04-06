#include "NodeActor.h"

#include "ComponentPlayer.h"
#include "ComponentKeyboard.h"
#include "ComponentPosition.h"
#include <typeinfo>

const std::set<const std::type_info *> NodeActor::gComponentTypes{ &typeid(ComponentKeyboard),&typeid(ComponentPlayer), &typeid(ComponentPosition) };