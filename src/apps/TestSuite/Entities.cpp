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

TEST(Entities, Copy)
{
    Entity entityOrigin;
    entityOrigin.addComponent(std::make_shared<ComponentA>(5));
    
    Entity entityCopy=entityOrigin;
    std::shared_ptr<ComponentA> copyComponentA = entityCopy.get<ComponentA>();
    copyComponentA->a = 10;
    
    CHECK_EQUAL(5, entityOrigin.get<ComponentA>()->a);
}
