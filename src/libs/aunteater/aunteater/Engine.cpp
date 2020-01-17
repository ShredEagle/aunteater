#include "Engine.h"
#include "System.h"

#include "Component.h"

using namespace aunteater;

weak_entity Engine::addEntity(const std::string & aName, Entity aEntity)
{
    auto insertionResult = mNamedEntities.left.insert(std::make_pair(aName, nullptr));
    if (!insertionResult.second)
    {
        throw std::invalid_argument("Named entity is already present in the engine"
                                    "with the same name.");
    }

    /// \todo Multithreading issue ahead
    // Note: cannot be done directly at insert, because addEntity has side effects which should
    //       not take place if the name was already present
    auto id = addEntity(aEntity);
    mNamedEntities.left.replace_data(insertionResult.first, id);
    return id;
}

weak_entity Engine::addEntity(Entity aEntity)
{
    // Note: cannot emplace_back, before C++17, it returns void
    weak_entity lastEntity = entityRefFrom(*mEntities.emplace(mEntities.end(), aEntity, this));
    addedEntity(lastEntity);
    return lastEntity;
}

/// \todo revisit, it compares an EntityId to a weak_entity
void Engine::removeEntity(weak_entity aEntity)
{
    mNamedEntities.right.erase(aEntity);
    removedEntity(aEntity);
    mEntities.remove_if([aEntity](const EntityWrapper &aElem)
                        {
                            return entityIdFrom(aElem) == aEntity;
                        });
}


void Engine::addedEntity(weak_entity aEntity)
{
    for (auto & typedFamily : mTypedFamilies)
    {
        typedFamily.second.addIfMatch(aEntity);
    }
}

void Engine::removedEntity(weak_entity aEntity)
{
    for (auto & typedFamily : mTypedFamilies)
    {
        typedFamily.second.removeIfPresent(aEntity);
    }
}

void Engine::addSystem(std::shared_ptr<System> aSystem)
{
    aSystem->addedToEngine(*this);
    mSystems.push_back(std::move(aSystem));
}

void Engine::update(double time)
{
    for (auto & system : mSystems)
    {
        system->update(time);
    }
}
