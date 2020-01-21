#include "Family.h"

#include "Engine.h"
#include "Entity.h"

#include <algorithm>

using namespace aunteater;

Family::Family(ArchetypeTypeSet aComponentsTypeInfo):
        mComponentsTypeInfo(std::move(aComponentsTypeInfo))
{}

void Family::addIfMatch(weak_entity aEntity)
{
    if (std::all_of(mComponentsTypeInfo.begin(), mComponentsTypeInfo.end(),
                    [&aEntity](ComponentTypeId compId)
                    {
                        return aEntity->has(compId);
                    }))
    {
        auto insertedIt = mEntities.insert(mEntities.end(), aEntity);
        if (!mEntitiesPositions.emplace(entityIdFrom(*aEntity), insertedIt).second)
        {
            throw std::logic_error("Entity already present in this family.");
        }
        broadcastNotification(&FamilyObserver::addedEntity, **insertedIt);
    }
}

void Family::removeIfPresent(entity_id aEntity)
{
    auto foundIt = mEntitiesPositions.find(entityIdFrom(*aEntity));
    if (foundIt != mEntitiesPositions.end())
    {
        broadcastNotification(&FamilyObserver::removedEntity, **(foundIt->second));
        mEntities.erase(foundIt->second);
        mEntitiesPositions.erase(foundIt);
    }
}

void Family::componentAddedToEntity(weak_entity aEntity, ComponentTypeId /*aComponent*/)
{
    if(!isPresent(aEntity))
    {
        addIfMatch(aEntity);
    }
}

void Family::componentRemovedFromEntity(entity_id aEntity, ComponentTypeId aComponent)
{
    if (includesComponent(aComponent))
    {
        removeIfPresent(aEntity);
    }
}

bool Family::isPresent(entity_id aEntity) const
{
    return mEntitiesPositions.find(aEntity) != mEntitiesPositions.end();
}

bool Family::includesComponent(ComponentTypeId aComponent) const
{
    return mComponentsTypeInfo.count(aComponent);
}

void Family::broadcastNotification(NotificationMethod aTargetMethod, LiveEntity &aEntity) const
{
    for(auto observer : mObservers)
    {
        (observer->*aTargetMethod)(aEntity);
    }
}

void Family::cancelObserverImpl(FamilyObserver *aObserver)
{
    /// \todo gsl::Expect prime candidate
    assert(std::find(mObservers.begin(), mObservers.end(), aObserver) != mObservers.end());
    mObservers.erase(std::find(mObservers.begin(), mObservers.end(), aObserver));
}

void Family::notifyOfExistingEntities(FamilyObserver *aObserver)
{
    for(weak_entity entity : mEntities)
    {
        broadcastNotification(&FamilyObserver::addedEntity, *entity);
    };
}

Family & Family::registerObserver(FamilyObserver *aObserver)
{
    mObservers.push_back(aObserver);
    notifyOfExistingEntities(aObserver);
    return *this;
}

Family & Family::cancelObserver(FamilyObserver *aObserver)
{
    cancelObserverImpl(aObserver);
    return *this;
}

//void Family::componentAddedToEntity(std::shared_ptr<Entity> aEntity, ComponentTypeId aComponent);
//void Family::componentRemovedFromEntity(std::shared_ptr<Entity> aEntity, ComponentTypeId aComponent);
/*
void Family::removeEntity(std::shared_ptr<Entity> aEntity)
{
    removeIfMatch(aEntity);
}

void Family::componentAddedToEntity(std::shared_ptr<Entity> aEntity, <#std::type_info *aComponent#>)
{

}
*/
