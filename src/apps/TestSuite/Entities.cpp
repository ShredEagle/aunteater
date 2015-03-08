#include "CommonComponents.h"

#include <aunteater/Engine.h>

/// ! MUST BE LAST ! ///
#include <CppUTest/TestHarness.h>

using namespace aunteater;

const ArchetypeTypeSet ArchetypeA::gComponentTypes{ &typeid(ComponentA) };

SimpleString StringFrom(Nodes)
{
    return "Not Implemented";
}

TEST_GROUP(Entities)
{
    
};

//Entity & emptyEntity()
//{
//    return Entity;
//    
//}
//
//Entity & getCompA_Entity()
//{
//    Entity
//}
TEST(Entities, ComponentType)
{
    ComponentA compA(5);
    ComponentB compB(5.0), compB_2(10.);
    
    ComponentTypeId idComponentB = compB.getTypeInfo(),
                    idComponentB_2 = compB_2.getTypeInfo(),
                    idComponentA = compA.getTypeInfo();
    
    CHECK_FALSE(idComponentB == idComponentA)
    CHECK_TRUE(idComponentB == idComponentB_2)
}

TEST(Entities, ComponentManagement)
{
    Entity entity;
    CHECK_FALSE(entity.has<ComponentA>())
    CHECK_FALSE(entity.has<ComponentB>())

    // Adding component
    entity.addComponent<ComponentB>(3.14);
    CHECK_FALSE(entity.has<ComponentA>())
    CHECK_TRUE(entity.has<ComponentB>())
    CHECK_EQUAL(3.14, entity.get<ComponentB>()->b)

    // Replacing component
    entity.addComponent<ComponentB>(900000000.);
    CHECK_EQUAL(900000000., entity.get<ComponentB>()->b)

    // Removing component
    entity.removeComponent<ComponentB>();
    CHECK_FALSE(entity.has<ComponentA>())
    CHECK_FALSE(entity.has<ComponentB>())
}

TEST(Entities, CopyControl)
{
    Entity entityOrigin;
    entityOrigin.addComponent<ComponentA>(5);

    {
        Entity entityCopy(entityOrigin);
        weak_component<ComponentA> copyComponentA = entityCopy.get<ComponentA>();
        CHECK_EQUAL(5, copyComponentA->a);
        copyComponentA->a = 1;
        CHECK_EQUAL(1, copyComponentA->a);

        CHECK_EQUAL(5, entityOrigin.get<ComponentA>()->a);
    }

    { // Probably equivalent in term un generated code as the previous case, but this is compiler-defined behavior.
        Entity entityCopy = entityOrigin;
        weak_component<ComponentA> copyComponentA = entityCopy.get<ComponentA>();
        CHECK_EQUAL(5, copyComponentA->a);
        copyComponentA->a = 10;
        CHECK_EQUAL(10, copyComponentA->a);
        
        CHECK_EQUAL(5, entityOrigin.get<ComponentA>()->a);
    }

    {
        Entity entityAssigned;
        entityAssigned = entityOrigin;
        weak_component<ComponentA> assignedComponentA = entityAssigned.get<ComponentA>();
        CHECK_EQUAL(5, assignedComponentA->a);
        assignedComponentA->a = 20;
        CHECK_EQUAL(20, assignedComponentA->a);
    }

    CHECK_EQUAL(5, entityOrigin.get<ComponentA>()->a);
}

TEST(Entities, AddEntities)
{
    Engine engine;
    
    Nodes nodesA_before = engine.getNodes<ArchetypeA>();
    CHECK(nodesA_before.size() == 0)
    
    Entity entity;
    entity.addComponent<ComponentA>(5);
    engine.addEntity(entity);
    
    Nodes nodesA_after = engine.getNodes<ArchetypeA>();
    CHECK(nodesA_after.size() == 1)
    
    CHECK_EQUAL(nodesA_before, nodesA_after)
}

TEST(Entities, RemoveEntities)
{
    Engine engine;
    
    Entity entity;
    entity.addComponent<ComponentA>(5);
    weak_entity firstEntity = engine.addEntity(entity);
    
    Nodes nodesA_added = engine.getNodes<ArchetypeA>();
    CHECK(nodesA_added.size() == 1)
    
    engine.removeEntity(firstEntity);
    Nodes nodesA_removed = engine.getNodes<ArchetypeA>();
    CHECK(nodesA_removed.size() == 0)
    
    CHECK_EQUAL(nodesA_removed, nodesA_added)
}
