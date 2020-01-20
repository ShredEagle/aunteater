#include "Family.h"

#include "Engine.h"
#include "Entity.h"

#include <algorithm>

using namespace aunteater;

Family::Family(ArchetypeTypeSet aComponentsTypeInfo):
        mComponentsTypeInfo(aComponentsTypeInfo)
{}

void Family::addIfMatch(weak_entity aEntity)
{
    if (std::all_of(mComponentsTypeInfo.begin(), mComponentsTypeInfo.end(),
                    [&aEntity](ComponentTypeId compId)
                    {
                        return aEntity->has(compId);
                    }))
    {
        mNodes.emplace_back(mComponentsTypeInfo, aEntity, Node::family_access());
        if (!mEntitiesToNodes.emplace(aEntity, --mNodes.end()).second)
        {
            throw std::runtime_error("Entity already present in this family.");
        }

        broadcastNotification(&FamilyObserver::addedNode, mNodes.back());
    }
}

void Family::removeIfPresent(entity_id aEntity)
{
    auto foundIt = mEntitiesToNodes.find(aEntity);
    if (foundIt != mEntitiesToNodes.end())
    {
        broadcastNotification(&FamilyObserver::removedNode, *(foundIt->second));

        mNodes.erase(foundIt->second);
        mEntitiesToNodes.erase(foundIt);
    }
}

void Family::componentAddedToEntity(weak_entity aEntity, ComponentTypeId aComponent)
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
    return mEntitiesToNodes.find(aEntity) != mEntitiesToNodes.end();
}

bool Family::includesComponent(ComponentTypeId aComponent) const
{
    return mComponentsTypeInfo.count(aComponent);
}

void Family::broadcastNotification(NotificationMethod aTargetMethod, Node &aNode) const
{
    for(auto observer : mObservers)
    {
        (observer->*aTargetMethod)(aNode);
    }
}

void Family::cancelObserverImpl(FamilyObserver *aObserver)
{
    /// \todo gsl::Expect prime candidate
    assert(std::find(mObservers.begin(), mObservers.end(), aObserver) != mObservers.end());
    mObservers.erase(std::find(mObservers.begin(), mObservers.end(), aObserver));
}

void Family::notifyOfExistingNodes(FamilyObserver *aObserver)
{
    for(Node &node : mNodes)
    {
        broadcastNotification(&FamilyObserver::addedNode, node);
    };
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
