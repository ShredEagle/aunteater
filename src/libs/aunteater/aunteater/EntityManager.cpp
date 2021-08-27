#include "EntityManager.h"
#include "System.h"

#include "Component.h"

using namespace aunteater;

weak_entity EntityManager::addEntity(const std::string & aName, Entity aEntity)
{
    auto insertionResult = mNamedEntities.left.insert(std::make_pair(aName, nullptr));
    if (!insertionResult.second)
    {
        throw std::invalid_argument("Named entity is already present in the entityManager"
                                    "with the same name.");
    }

    /// \todo Multithreading issue ahead
    // Note: cannot be done directly at insert, because addEntity has side effects which should
    //       not take place if the name was already present
    auto id = addEntity(std::move(aEntity));
    mNamedEntities.left.replace_data(insertionResult.first, id);
    return id;
}

weak_entity EntityManager::addEntity(Entity aEntity)
{
    // Note: cannot emplace_back, before C++17 it returns void
    weak_entity lastEntity =
        entityRefFrom(*mEntities.emplace(mEntities.end(), std::move(aEntity), *this, EntityManagerTag{}));
    notifyAdditionToFamilies(lastEntity);
    return lastEntity;
}

/// TODO revisit, it compares an EntityId to a weak_entity, causing const-ness complications
///   (low level const in entity_id prevents matching against keys that are not low level const)
///   Take a look at "Transparent comparators"
///   Should allow constness on the mEntitiesToRemove pointers
void EntityManager::removeEntities()
{
    /// TODO Measure if it is more efficient:
    ///   * to iterate flagged entities and look them up one by one in the associative containers (current)
    ///   * to iterate the associative containers entirely each time, and remove matching flagged entities
    /// TODO more constness here

    std::set<weak_entity> removedEntities;
    // Note: this outer loop is required in case a family observer marks additional nodes for removal
    // see EntityManager_tests.cpp "Nested entities removal" scenario
    while(!mEntitiesToRemove.empty())
    {
        for (auto entityIt = mEntitiesToRemove.begin();
             entityIt != mEntitiesToRemove.end();
             /* in body */)
        {
            mNamedEntities.right.erase(*entityIt);
            notifyRemovalToFamilies(*entityIt);
            // set::extract() invalidates the current iterator: use post-increment to return a copy
            removedEntities.insert(mEntitiesToRemove.extract(entityIt++));
        }
    }

    /// TODO LiveEntity should be const here
    mEntities.remove_if([&removedEntities](LiveEntity &aElem)
    {
        return removedEntities.count(&aElem); // contains() is C++20
    });
}

void EntityManager::removeComponents()
{
    // Note: this outer loop is required in case a family observer marks additional components for removal
    while(!mComponentsToRemove.empty())
    {
        for (auto componentIt = mComponentsToRemove.begin();
             componentIt != mComponentsToRemove.end();
             componentIt = mComponentsToRemove.erase(componentIt))
        {
            forEachFamily([componentIt](Family &family)
            {
              family.componentRemovedFromEntity(entityIdFrom(componentIt->first), componentIt->second);
            });
            componentIt->first->remove_impl(componentIt->second);
        }
    }
}


void EntityManager::notifyAdditionToFamilies(weak_entity aEntity)
{
    for (auto & typedFamily : mTypedFamilies)
    {
        typedFamily.second.addIfMatch(aEntity);
    }
}

void EntityManager::notifyRemovalToFamilies(entity_id aEntity)
{
    for (auto & typedFamily : mTypedFamilies)
    {
        typedFamily.second.removeIfPresent(aEntity);
    }
}
