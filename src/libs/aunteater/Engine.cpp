#include "Engine.h"

#include "Component.h"

using namespace aunteater;

Handle<Entity> Engine::addEntity(const std::string & aName, Entity aEntity)
{
    auto insertionResult = mNamedEntities.left.insert(std::make_pair(aName, Handle<Entity>(0)));
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

Handle<Entity> Engine::addEntity(Entity aEntity)
{
    mEntities.push_back(aEntity);
    return Handle<Entity>(mEntities.size()-1);
}

void Engine::removeEntity(Handle<Entity> aId)
{
    mNamedEntities.right.erase(aId);
    mEntities.erase(mEntities.begin()+aId.get());
}


void Engine::addedEntity(Handle<Entity> aEntity)
{
    for (auto & typedFamily : mTypedFamilies)
    {
        typedFamily.second.testEntityInclusion(aEntity.deref(mEntities));
    }
}