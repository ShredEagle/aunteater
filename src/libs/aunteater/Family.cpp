#include "Family.h"

#include "Engine.h"
#include "Entity.h"

#include <algorithm>

using namespace aunteater;

Family::Family(Engine & aEngine, ArchetypeTypeSet aComponentsTypeInfo):
        mEngine(aEngine),
        mComponentsTypeInfo(aComponentsTypeInfo)
{
    
}

void Family::testEntityInclusion(Handle<Entity> aEntity)
{
    addIfMatch(aEntity);
}

void Family::addIfMatch(Handle<Entity> aEntity)
{
    if (std::all_of(mComponentsTypeInfo.begin(), mComponentsTypeInfo.end(),
                    [&aEntity](const std::type_info *compId){return aEntity->has(compId);}))
    {
        mNodes.emplace_back(mComponentsTypeInfo, aEntity, Node::family_access());
    }
}

void Family::removeIfPresent(Handle<Entity> aEntity)
{
    auto foundIt = mEntities.find(aEntity);
    if (foundIt != mEntities.end())
    {
        mNodes.erase(foundIt->second);
        mEntities.erase(foundIt);
    }
}
/*
void Family::removeEntity(std::shared_ptr<Entity> aEntity)
{
    removeIfMatch(aEntity);
}

void Family::componentAddedToEntity(std::shared_ptr<Entity> aEntity, <#std::type_info *aComponent#>)
{
    
}
*/