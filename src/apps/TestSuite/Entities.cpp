#include <aunteater/Engine.h>

#include <CppUTest/TestHarness.h>

using namespace aunteater;

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
    entityOrigin.addComponent(std::make_shared<ComponentA>(5));
    
    Entity entityCopy=entityOrigin;
    std::shared_ptr<ComponentA> copyComponentA = entityCopy.get<ComponentA>();
    copyComponentA->a = 10;
    
    CHECK_EQUAL(5, entityOrigin.get<ComponentA>()->a);
}
