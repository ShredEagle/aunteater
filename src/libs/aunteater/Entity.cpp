#include "Entity.h"

#include "Component.h"

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

Entity & Entity::removeComponent(ComponentTypeId aComponentId)
{
    mComponents.erase(aComponentId);
    return *this;
}

void Entity::addComponent(own_component<> aComponent)
{
    // This is a custom implementation of map::insert_or_assign()
    //   we cannot use the branch version (inserting, and only optionally assigning),
    //   because the mapped_type is non-copyable, so we have to move it (only once)
    auto insertionResult = mComponents.emplace(aComponent->getTypeInfo(), nullptr);
    insertionResult.first->second = std::move(aComponent);
}