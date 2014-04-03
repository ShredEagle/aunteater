#include "Entity.h"

#include "Component.h"

using namespace aunteater;


void Entity::addComponent(std::shared_ptr<Component> aComponent)
{
    /// \todo remove the initial test
    auto foundIt = mComponents.find(&aComponent->getTypeInfo());
    if (foundIt != mComponents.end())
    {
        foundIt->second = std::move(aComponent);
    }
    else
    {
        mComponents.insert(std::make_pair(&aComponent->getTypeInfo(), aComponent));
    }

}

void Entity::removeComponent(const std::type_info & aComponentId)
{
    mComponents.erase(&aComponentId);
}