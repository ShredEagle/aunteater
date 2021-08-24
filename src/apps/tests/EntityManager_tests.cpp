#include "catch.hpp"

#include <aunteater/EntityManager.h>
#include <aunteater/SystemManager.h>

using namespace aunteater;


// Chained component
class ComponentList : public aunteater::Component<ComponentList>
{
public:
    ComponentList(weak_entity aNext = nullptr):
        next{aNext}
    {}

    weak_entity next;
};


// FamilyObserver recursively deleting entities in the ComponentList chain
class RecursiveRemover : public FamilyObserver
{
public:
    RecursiveRemover(EntityManager & aEntityManager) :
        entityManager(aEntityManager)
    {}

    void addedEntity(LiveEntity &aEntity) override
    {}

    void removedEntity(LiveEntity &aEntity) override
    {
        for(auto next = aEntity.get<ComponentList>().next;
            next != nullptr;
            next = next->get<ComponentList>().next)
        {
            entityManager.markToRemove(next);
        }
    }

    EntityManager & entityManager;
};


SCENARIO("Nested entities removal")
{
    GIVEN("A Family of chained components and an observer recursively deleting entities")
    {
        EntityManager entityManager;
        SystemManager<> systemManager{entityManager};
        Family & listFamily = entityManager.getFamily<Archetype<ComponentList>>();

        REQUIRE(entityManager.countEntities() == 0);
        REQUIRE(listFamily.size() == 0);

        RecursiveRemover remover{entityManager};
        listFamily.registerObserver(&remover);

        weak_entity a = entityManager.addEntity(Entity{}.add<ComponentList>());
        weak_entity b = entityManager.addEntity(Entity{}.add<ComponentList>());

        REQUIRE(entityManager.countEntities() == 2);
        REQUIRE(listFamily.size() == 2);

        weak_entity min = std::min(a, b);
        weak_entity max = std::max(a, b);

        WHEN("The entities are chained in increasing address order")
        {
            min->get<ComponentList>().next = max;

            // Sanity check
            systemManager.update(Timer{});
            REQUIRE(listFamily.size() == 2);

            WHEN("The tail is removed")
            {
                entityManager.markToRemove(max);
                // Sanity check
                REQUIRE(listFamily.size() == 2);

                systemManager.update(Timer{});

                THEN("The tail has been removed from the family")
                {
                    REQUIRE(listFamily.size() == 1);
                }
                THEN("The tail has been removed from the entityManager")
                {
                    REQUIRE(entityManager.countEntities() == 1);
                }
            }

            WHEN("The root is removed")
            {
                entityManager.markToRemove(min);
                systemManager.update(Timer{});

                THEN("Both head and tail have been removed from the family")
                {
                    REQUIRE(listFamily.size() == 0);
                }
                THEN("Both head and tail have been removed from the entityManager")
                {
                    REQUIRE(entityManager.countEntities() == 0);
                }
            }
        }

        WHEN("The entities are chained in decreasing address order")
        {
            max->get<ComponentList>().next = min;

            WHEN("The tail is removed")
            {
                entityManager.markToRemove(min);
                systemManager.update(Timer{});

                THEN("The tail has been removed from the family")
                {
                    REQUIRE(listFamily.size() == 1);
                }
                THEN("The tail has been removed from the entityManager")
                {
                    REQUIRE(entityManager.countEntities() == 1);
                }
            }

            WHEN("The root is removed")
            {
                entityManager.markToRemove(max);
                systemManager.update(Timer{});

                THEN("Both head and tail have been removed from the family")
                {
                    // Note: this statement is the one motivating this whole scenario:
                    // with the initial approach were marking entity for removal insert them in a set later iterated
                    // nested removal could fail depending on the relative position in the set
                    // (position of the currently removed entity vs the position of the entity it is recursively marking for removal)
                    REQUIRE(listFamily.size() == 0);
                }
                THEN("Both head and tail have been removed from the entityManager")
                {
                    REQUIRE(entityManager.countEntities() == 0);
                }
            }
        }
    }
}
