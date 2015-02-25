#include "Entity.h"

#include "Component.h"

using namespace aunteater;


void Entity::addComponent(own_component<> aComponent)
{
    auto insertionResult =
        mComponents.insert(std::make_pair(aComponent->getTypeInfo(), aComponent));
    
    if(!insertionResult.second)
    {
        insertionResult.first->second = aComponent;
    }
}