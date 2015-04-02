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
    auto id = addEntity(aEntity);
    mNamedEntities.left.replace_data(insertionResult.first, id);
    return id;
}

weak_entity Engine::addEntity(Entity aEntity)
{
    mEntities.emplace_back(aEntity, this);
    //auto lastEntity(makeHandle(mEntities, mEntities.size()-1));
    weak_entity lastEntity = entityRefFrom(mEntities.back());
    addedEntity(lastEntity);
    return lastEntity;
}

void Engine::removeEntity(weak_entity aEntity)
{
    mNamedEntities.right.erase(aEntity);
    removedEntity(aEntity);
    mEntities.remove_if([aEntity](const EntityWrapper &aElem){ return entityIdFrom(aElem) == aEntity; });
}


void Engine::addedEntity(weak_entity aEntity)
{
    for (auto & typedFamily : mTypedFamilies)
    {
        typedFamily.second.testEntityInclusion(aEntity);
    }
}

void Engine::removedEntity(weak_entity aEntity)
{
    for (auto & typedFamily : mTypedFamilies)
    {
        typedFamily.second.removeIfPresent(aEntity);
    }
}

void Engine::addSystem(System *aSystem)
{
    mSystems.push_back(aSystem);
}

void Engine::update(float time)
{
    for (System * system : mSystems)
    {
        system->update(time);
    }
}