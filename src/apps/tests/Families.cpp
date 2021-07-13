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
                entity.add<ComponentB>(5);
                engine.addEntity("entity_componentB", std::move(entity));
                REQUIRE(0 == NodesOfArchetypeA.size());
            }

            {
                Entity entity;
                entity.add<ComponentA>(5);
                engine.addEntity("entity_componentA", std::move(entity));
            }
            REQUIRE(1 == NodesOfArchetypeA.size());

            engine.markToRemove("entity_componentB");
            engine.update(Timer{});
            REQUIRE(1 == NodesOfArchetypeA.size());

            engine.markToRemove("entity_componentA");
            engine.update(Timer{});
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
                entity.add<ComponentA>(5);
                engine.addEntity("aunt", std::move(entity));
            }

            REQUIRE(1 == NodesOfArchetypeA.size());

            auto entity = engine.getEntity("aunt");
            entity->remove<ComponentA>();
            REQUIRE(0 == NodesOfArchetypeA.size());

            entity->add<ComponentB>(51.);
            REQUIRE(0 == NodesOfArchetypeA.size());

            entity->add<ComponentA>(51);
            REQUIRE(1 == NodesOfArchetypeA.size());

            entity->remove<ComponentB>();
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
            weak_entity firstEntity = engine.addEntity(Entity().add<ComponentA>(5));
            REQUIRE(1 == observer.addNotificationCount);

            weak_entity secondEntity = engine.addEntity(Entity().add<ComponentA>(5).add<ComponentB>(52.));
            REQUIRE(2 == observer.addNotificationCount);

            THEN("Removing components from Entities triggers notifications")
            {
                secondEntity->remove<ComponentB>();
                REQUIRE(0 == observer.removeNotificationCount);

                secondEntity->remove<ComponentA>();
                REQUIRE(1 == observer.removeNotificationCount);
            }

            THEN("Removing Entities triggers notifications")
            {
                engine.markToRemove(firstEntity);
                engine.update(Timer{});
                REQUIRE(1 == observer.removeNotificationCount);

                REQUIRE(2 == observer.addNotificationCount);
            }
        }

        GIVEN("A second observer")
        {
            engine.addEntity(Entity().add<ComponentA>(10));
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
