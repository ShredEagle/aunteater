#include <aunteater/Component.h>
#include <aunteater/Engine.h>

#include <CppUTest/TestHarness.h>

using namespace aunteater;

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

class ComponentA : public Component
{
public:
    ComponentA(int aInteger):
            a(aInteger)
    {}
    
    int a;
};

class ArchetypeA
{
public:
    static const ArchetypeTypeSet gComponentTypes;
};

const ArchetypeTypeSet ArchetypeA::gComponentTypes{ &typeid(ComponentA) };

TEST(Entities, ComponentType)
{
    Component base;
    ComponentA compA(5);
    
    ComponentTypeId idBase = base.getTypeInfo(),
                    idComponentA = compA.getTypeInfo();
    
    CHECK_FALSE(idBase == idComponentA)
}

TEST(Entities, Copy)
{
    Entity entityOrigin;
    entityOrigin.addComponent<ComponentA>(5);
    
    Entity entityCopy=entityOrigin;
    weak_component<ComponentA> copyComponentA = entityCopy.get<ComponentA>();
    copyComponentA->a = 10;
    
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
    Handle<Entity> firstEntity = engine.addEntity(entity);
    
    Nodes nodesA_added = engine.getNodes<ArchetypeA>();
    CHECK(nodesA_added.size() == 1)
    
    engine.removeEntity(firstEntity);
    Nodes nodesA_removed = engine.getNodes<ArchetypeA>();
    CHECK(nodesA_removed.size() == 0)
    
    CHECK_EQUAL(nodesA_removed, nodesA_added)
}
