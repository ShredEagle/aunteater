#include "CommonComponents.h"

#include "catch.hpp"

#include <aunteater/Engine.h>

using namespace aunteater;


SCENARIO("Family management on entities addition/removal")
{
    GIVEN("An Engine and an Archetype")
    {
        Engine engine;
        Family & NodesOfArchetypeA = engine.getFamily<ArchetypeA>();
        REQUIRE(0 == NodesOfArchetypeA.size());

        SECTION("Entities addition/removal")
        {
            {
                Entity entity;
                entity.addComponent<ComponentB>(5);
                engine.addEntity("entity_componentB", std::move(entity));
                REQUIRE(0 == NodesOfArchetypeA.size());
            }

            {
                Entity entity;
                entity.addComponent<ComponentA>(5);
                engine.addEntity("entity_componentA", std::move(entity));
            }
            REQUIRE(1 == NodesOfArchetypeA.size());

            engine.removeEntity("entity_componentB");
            REQUIRE(1 == NodesOfArchetypeA.size());

            engine.removeEntity("entity_componentA");
            REQUIRE(0 == NodesOfArchetypeA.size());
        }
    }
}


SCENARIO("Family management on components update")
{
    GIVEN("An Engine and an Archetype")
    {
        Engine engine;
        Family & NodesOfArchetypeA = engine.getFamily<ArchetypeA>();

        THEN("Manipulating and Entity's Components updates the Family")
        {
            {
                Entity entity;
                entity.addComponent<ComponentA>(5);
                engine.addEntity("aunt", std::move(entity));
            }

            REQUIRE(1 == NodesOfArchetypeA.size());

            auto entity = engine.getEntity("aunt");
            entity->removeComponent<ComponentA>();
            REQUIRE(0 == NodesOfArchetypeA.size());

            entity->addComponent<ComponentB>(51.);
            REQUIRE(0 == NodesOfArchetypeA.size());

            entity->addComponent<ComponentA>(51);
            REQUIRE(1 == NodesOfArchetypeA.size());

            entity->removeComponent<ComponentB>();
            REQUIRE(1 == NodesOfArchetypeA.size());
        }
    }
}

SCENARIO("Family observation")
{
    GIVEN("An Engine, an Observer and an Archetype")
    {
        Engine engine;

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
        engine.getFamily<ArchetypeA>().registerObserver(&observer);

        THEN("The observer is not notified while there are no Nodes")
        {
            REQUIRE(0 == observer.addNotificationCount);
        }


        THEN("Addition removal of Entities matching the Archetype triggers notifications")
        {
            weak_entity firstEntity = engine.addEntity(Entity().addComponent<ComponentA>(5));
            REQUIRE(1 == observer.addNotificationCount);

            weak_entity secondEntity = engine.addEntity(Entity().addComponent<ComponentA>(5).addComponent<ComponentB>(52.));
            REQUIRE(2 == observer.addNotificationCount);

            THEN("Removing components from Entities triggers notifications")
            {
                secondEntity->removeComponent<ComponentB>();
                REQUIRE(0 == observer.removeNotificationCount);

                secondEntity->removeComponent<ComponentA>();
                REQUIRE(1 == observer.removeNotificationCount);
            }

            THEN("Removing Entities triggers notifications")
            {
                engine.removeEntity(firstEntity);
                REQUIRE(1 == observer.removeNotificationCount);

                REQUIRE(2 == observer.addNotificationCount);
            }
        }

        GIVEN("A second observer")
        {
            engine.addEntity(Entity().addComponent<ComponentA>(10));
            TestObserver posterioriObserver;
            engine.getFamily<ArchetypeA>().registerObserver(&posterioriObserver);

            THEN("It should be notified of existing nodes in the family of interest.")
            {
                REQUIRE(1 == posterioriObserver.addNotificationCount);
                REQUIRE(0 == posterioriObserver.removeNotificationCount);
            }
        }
    }
}
