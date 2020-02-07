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
    auto id = addEntity(std::move(aEntity));
    mNamedEntities.left.replace_data(insertionResult.first, id);
    return id;
}

weak_entity Engine::addEntity(Entity aEntity)
{
    // Note: cannot emplace_back, before C++17 it returns void
    weak_entity lastEntity =
        entityRefFrom(*mEntities.emplace(mEntities.end(), std::move(aEntity), *this, EngineTag{}));
    notifyAdditionToFamilies(lastEntity);
    return lastEntity;
}

/// TODO revisit, it compares an EntityId to a weak_entity, causing const-ness complications
///   (low level const in entity_id prevents matching against keys that are not low level const)
///   Take a look at "Transparent comparators"
///   Should allow constness on the mEntitiesToRemove pointers
void Engine::removeEntities()
{
    /// TODO Measure if it is more efficient:
    ///   * to iterate flagged entities and look them up one by one in the associative containers (current)
    ///   * to iterate the associative containers entirely each time, and remove matching flagged entities
    /// TODO more constness here
    for(weak_entity entity : mEntitiesToRemove)
    {
        mNamedEntities.right.erase(entity);
        notifyRemovalToFamilies(entity);
    }

    /// TODO LiveEntity should be const here
    mEntities.remove_if([this](LiveEntity &aElem)
    {
        return this->mEntitiesToRemove.count(&aElem); // contains() is C++20
    });
    mEntitiesToRemove.clear();
}


void Engine::notifyAdditionToFamilies(weak_entity aEntity)
{
    for (auto & typedFamily : mTypedFamilies)
    {
        typedFamily.second.addIfMatch(aEntity);
    }
}

void Engine::notifyRemovalToFamilies(entity_id aEntity)
{
    for (auto & typedFamily : mTypedFamilies)
    {
        typedFamily.second.removeIfPresent(aEntity);
    }
}

void Engine::addSystem(std::shared_ptr<System> aSystem)
{
    mSystems.push_back(std::move(aSystem));
}

void Engine::update(double time)
{
    for (auto & system : mSystems)
    {
        system->update(time);
    }
    removeEntities();
}
