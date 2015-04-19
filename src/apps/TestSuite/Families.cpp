#include "CommonComponents.h"

#include <aunteater/Engine.h>

/// ! MUST BE LAST ! ///
#include <CppUTest/TestHarness.h>

using namespace aunteater;

TEST_GROUP(Families)
{};

TEST(Families, AddRemoveEntity)
{
    Engine engine;
    std::list<Node> &NodesOfArchetypeA = engine.getNodes<ArchetypeA>();
    CHECK_EQUAL(0, NodesOfArchetypeA.size());

    {
        Entity entity;
        entity.addComponent<ComponentB>(5);
        engine.addEntity("entity_componentB", std::move(entity));
    }
    CHECK_EQUAL(0, NodesOfArchetypeA.size());

    {
        Entity entity;
        entity.addComponent<ComponentA>(5);
        engine.addEntity("entity_componentA", std::move(entity));
    }
    CHECK_EQUAL(1, NodesOfArchetypeA.size());

    engine.removeEntity("entity_componentB");
    CHECK_EQUAL(1, NodesOfArchetypeA.size());

    engine.removeEntity("entity_componentA");
    CHECK_EQUAL(0, NodesOfArchetypeA.size());
}

TEST(Families, UpdatesOnComponent)
{
    Engine engine;
    std::list<Node> &NodesOfArchetypeA = engine.getNodes<ArchetypeA>();

    {
        Entity entity;
        entity.addComponent<ComponentA>(5);
        engine.addEntity("aunt", std::move(entity));
    }

    CHECK_EQUAL(1, NodesOfArchetypeA.size());

    auto entity = engine.getEntity("aunt");
    entity->removeComponent<ComponentA>();
    CHECK_EQUAL(0, NodesOfArchetypeA.size());

    entity->addComponent<ComponentB>(51.);
    CHECK_EQUAL(0, NodesOfArchetypeA.size());

    entity->addComponent<ComponentA>(51);
    CHECK_EQUAL(1, NodesOfArchetypeA.size());

    entity->removeComponent<ComponentB>();
    CHECK_EQUAL(1, NodesOfArchetypeA.size());
}

TEST(Families, FamilyObservation)
{
    Engine engine;

    struct TestObserver : public FamilyObserver
    {
        virtual void addedNode(Node &aNode) override
        {
            ++addNotificationCount;
        }

        virtual void removedNode(Node &aNode) override
        {
            ++removeNotificationCount;
        }

        unsigned addNotificationCount = 0;
        unsigned removeNotificationCount = 0;
    };

    TestObserver observer;
    engine.registerToNodes<ArchetypeA>(&observer);

    CHECK_EQUAL(0, observer.addNotificationCount);
    weak_entity fistEntity = engine.addEntity(Entity().addComponent<ComponentA>(5));
    CHECK_EQUAL(1, observer.addNotificationCount);

    weak_entity secondEntity = engine.addEntity(Entity().addComponent<ComponentA>(5).addComponent<ComponentB>(52.));
    CHECK_EQUAL(2, observer.addNotificationCount);

    secondEntity->removeComponent<ComponentB>();
    CHECK_EQUAL(0, observer.removeNotificationCount);

    secondEntity->removeComponent<ComponentA>();
    CHECK_EQUAL(1, observer.removeNotificationCount);

    engine.removeEntity(fistEntity);
    CHECK_EQUAL(2, observer.removeNotificationCount);

    CHECK_EQUAL(2, observer.addNotificationCount);
}