#include "CommonComponents.h"

#include "catch.hpp"

#include <aunteater/EntityManager.h>
#include <aunteater/SystemManager.h>

using namespace aunteater;


SCENARIO("Family management on entities addition/removal")
{
    GIVEN("An EntityManager and an Archetype")
    {
        EntityManager entityManager;
        SystemManager systemManager{entityManager};

        Family & NodesOfArchetypeA = entityManager.getFamily<ArchetypeA>();
        REQUIRE(0 == NodesOfArchetypeA.size());

        SECTION("Entities addition/removal")
        {
            {
                Entity entity;
                entity.add<ComponentB>(5);
                entityManager.addEntity("entity_componentB", std::move(entity));
                REQUIRE(0 == NodesOfArchetypeA.size());
            }

            {
                Entity entity;
                entity.add<ComponentA>(5);
                entityManager.addEntity("entity_componentA", std::move(entity));
            }
            REQUIRE(1 == NodesOfArchetypeA.size());

            entityManager.markToRemove("entity_componentB");
            systemManager.update(Timer{});
            REQUIRE(1 == NodesOfArchetypeA.size());

            entityManager.markToRemove("entity_componentA");
            systemManager.update(Timer{});
            REQUIRE(0 == NodesOfArchetypeA.size());
        }
    }
}


SCENARIO("Family management on components update")
{
    GIVEN("An EntityManager and an Archetype")
    {
        EntityManager entityManager;
        SystemManager systemManager{entityManager};
        Family & NodesOfArchetypeA = entityManager.getFamily<ArchetypeA>();

        THEN("Manipulating and Entity's Components updates the Family")
        {
            {
                Entity entity;
                entity.add<ComponentA>(5);
                entityManager.addEntity("aunt", std::move(entity));
            }

            REQUIRE(1 == NodesOfArchetypeA.size());

            auto entity = entityManager.getEntity("aunt");
            entity->markComponentToRemove<ComponentA>();
            // The component is not removed before the update step completes.
            REQUIRE(1 == NodesOfArchetypeA.size());
            systemManager.update(Timer{});
            REQUIRE(0 == NodesOfArchetypeA.size());

            entity->add<ComponentB>(51.);
            REQUIRE(0 == NodesOfArchetypeA.size());

            entity->add<ComponentA>(51);
            REQUIRE(1 == NodesOfArchetypeA.size());

            entity->markComponentToRemove<ComponentB>();
            systemManager.update(Timer{});
            REQUIRE(1 == NodesOfArchetypeA.size());
        }
    }
}

SCENARIO("Family observation")
{
    GIVEN("An EntityManager, an Observer and an Archetype")
    {
        EntityManager entityManager;
        SystemManager systemManager{entityManager};

        struct TestObserver : public FamilyObserver
        {
            virtual void addedEntity(LiveEntity &aEntity) override
            {
                ++addNotificationCount;
            }

            virtual void removedEntity(LiveEntity &aEntity) override
            {
                ++removeNotificationCount;
            }

            unsigned addNotificationCount = 0;
            unsigned removeNotificationCount = 0;
        };

        TestObserver observer;
        entityManager.getFamily<ArchetypeA>().registerObserver(&observer);

        THEN("The observer is not notified while there are no Nodes")
        {
            REQUIRE(0 == observer.addNotificationCount);
        }


        THEN("Addition removal of Entities matching the Archetype triggers notifications")
        {
            weak_entity firstEntity = entityManager.addEntity(Entity().add<ComponentA>(5));
            REQUIRE(1 == observer.addNotificationCount);

            weak_entity secondEntity = entityManager.addEntity(Entity().add<ComponentA>(5).add<ComponentB>(52.));
            REQUIRE(2 == observer.addNotificationCount);

            THEN("Removing components from Entities triggers notifications")
            {
                secondEntity->markComponentToRemove<ComponentB>();
                systemManager.update(Timer{});
                REQUIRE(0 == observer.removeNotificationCount);

                secondEntity->markComponentToRemove<ComponentA>();
                systemManager.update(Timer{});
                REQUIRE(1 == observer.removeNotificationCount);
            }

            THEN("Removing Entities triggers notifications")
            {
                entityManager.markToRemove(firstEntity);
                systemManager.update(Timer{});
                REQUIRE(1 == observer.removeNotificationCount);

                REQUIRE(2 == observer.addNotificationCount);
            }
        }

        GIVEN("A second observer")
        {
            entityManager.addEntity(Entity().add<ComponentA>(10));
            TestObserver posterioriObserver;
            entityManager.getFamily<ArchetypeA>().registerObserver(&posterioriObserver);

            THEN("It should be notified of existing nodes in the family of interest.")
            {
                REQUIRE(1 == posterioriObserver.addNotificationCount);
                REQUIRE(0 == posterioriObserver.removeNotificationCount);
            }
        }
    }
}
