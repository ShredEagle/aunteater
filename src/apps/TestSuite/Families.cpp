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

    {
        Entity entity;
        entity.addComponent<ComponentA>(5);
        engine.addEntity("aunt", std::move(entity));
    }

    std::list<Node> &NodesOfArchetypeA = engine.getNodes<ArchetypeA>();
    CHECK_EQUAL(1, NodesOfArchetypeA.size());

    auto entity = engine.getEntity("aunt");
    entity->removeComponent<ComponentA>();
    CHECK_EQUAL(0, NodesOfArchetypeA.size());
}