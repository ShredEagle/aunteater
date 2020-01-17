#include "Entity.h"

#include "Component.h"
#include "Engine.h"

using namespace aunteater;

Entity::Entity(const Entity &aOther)
{
    std::for_each(aOther.mComponents.begin(), aOther.mComponents.end(), [this](const auto &pair)
                  {
                      mComponents.emplace(pair.first, clone(pair.second));
                  });
}

Entity & Entity::operator=(Entity aRhs)
{
    swap(*this, aRhs);
    return *this;
}

Entity::~Entity()
{}

void Entity::addComponent(own_component<> aComponent)
{
    // This is a custom implementation of map::insert_or_assign()
    //   we cannot use the branch version (inserting, and only optionally assigning),
    //   because the mapped_type is non-copyable, so we have to move it (only once)
    auto insertionResult = mComponents.emplace(aComponent->getTypeInfo(), nullptr);
    insertionResult.first->second = std::move(aComponent);
    if(insertionResult.second && mOwner)
    {
        weak_component<> comp = weakFromOwn(insertionResult.first->second);
        ComponentTypeId compType = comp->getTypeInfo();
        mOwner->entityCompositionChanged([this, compType](Family &family)
                                         {
                                            family.componentAddedToEntity(this, compType);
                                         });
    }
}

void Entity::removeNotifyOwner(ComponentTypeId aComponentId)
{
    if(mOwner)
    {
        mOwner->entityCompositionChanged([this, aComponentId](Family &family)
                                            { family.componentRemovedFromEntity(this, aComponentId); });
    }
}
