#include "Entity.h"

#include "EntityManager.h"

using namespace aunteater;

Entity::Entity(const Entity &aOther)
{
    std::for_each(aOther.mComponents.begin(), aOther.mComponents.end(), [this](const auto &pair)
                  {
                      mComponents.emplace(pair.first, clone(pair.second));
                  });
}

Entity::Entity(Entity &&aOther) :
    mComponents(std::move(aOther.mComponents))
{}

Entity & Entity::operator=(Entity aRhs)
{
    swap(*this, aRhs);
    return *this;
}

bool Entity::addComponent(own_component<> aComponent)
{
    // This is a custom implementation of map::insert_or_assign()
    auto insertionResult = mComponents.emplace(aComponent->getTypeInfo(), nullptr);
    insertionResult.first->second = std::move(aComponent);
    return insertionResult.second;
}
