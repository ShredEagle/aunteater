#include "Entity.h"

#include "Component.h"

using namespace aunteater;


void Entity::addComponent(std::shared_ptr<Component> aComponent)
{
    auto insertionResult =
        mComponents.insert(std::make_pair(aComponent->getTypeInfo(), aComponent));
    
    if(!insertionResult.second)
    {
        insertionResult.first->second = aComponent;
    }
}

void Entity::removeComponent(const std::type_info & aComponentId)
{
    mComponents.erase(&aComponentId);
}