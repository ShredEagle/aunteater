#include "CommonComponents.h"

#include "catch.hpp"

#include <aunteater/Engine.h>

using namespace aunteater;

const ArchetypeTypeSet ArchetypeA::gComponentTypes{ &typeid(ComponentA) };

SCENARIO("Component identifiers")
{
    GIVEN("Three components, one being distinct")
    {
        ComponentA compA(5);
        ComponentB compB(5.0), compB_2(10.);

        THEN("Their identifiers are matching accordingly")
        {
            ComponentTypeId idComponentB = compB.getTypeInfo(),
                            idComponentB_2 = compB_2.getTypeInfo(),
                            idComponentA = compA.getTypeInfo();

            REQUIRE(idComponentB != idComponentA);
            REQUIRE(idComponentB == idComponentB_2);
        }
    }
}


SCENARIO("Component management")
{
    GIVEN("An Entity")
    {
        Entity entity;

        THEN("It does not contain components")
        {
            REQUIRE_FALSE(entity.has<ComponentA>());
            REQUIRE_FALSE(entity.has<ComponentB>());
        }

        WHEN("Adding a component to the Entity")
        {
            // Adding component
            entity.addComponent<ComponentB>(3.14);
            THEN("It contains the component, but not another")
            {
                REQUIRE_FALSE(entity.has<ComponentA>());
                REQUIRE(entity.has<ComponentB>());
                REQUIRE(3.14 == entity.get<ComponentB>()->b);
            }

            WHEN("Adding the same component")
            {
                entity.addComponent<ComponentB>(900000000.);
                THEN("The Component is replaced")
                {
                    REQUIRE(900000000. == entity.get<ComponentB>()->b);
                }
            }

            WHEN("Removing the Component from the Entity")
            {
                entity.removeComponent<ComponentB>();
                THEN("It does not contain any component anymore")
                {
                    REQUIRE_FALSE(entity.has<ComponentA>());
                    REQUIRE_FALSE(entity.has<ComponentB>());
                }
            }
        }
    }
}

//TEST(Entities, CopyControl)
//{
//    Entity entityOrigin;
//    entityOrigin.addComponent<ComponentA>(5);
//
//    {
//        Entity entityCopy(entityOrigin);
//        weak_component<ComponentA> copyComponentA = entityCopy.get<ComponentA>();
//        CHECK_EQUAL(5, copyComponentA->a);
//        copyComponentA->a = 1;
//        CHECK_EQUAL(1, copyComponentA->a);
//
//        CHECK_EQUAL(5, entityOrigin.get<ComponentA>()->a);
//    }
//
//    { // Probably equivalent in term un generated code as the previous case, but this is compiler-defined behavior.
//        Entity entityCopy = entityOrigin;
//        weak_component<ComponentA> copyComponentA = entityCopy.get<ComponentA>();
//        CHECK_EQUAL(5, copyComponentA->a);
//        copyComponentA->a = 10;
//        CHECK_EQUAL(10, copyComponentA->a);
//
//        CHECK_EQUAL(5, entityOrigin.get<ComponentA>()->a);
//    }
//
//    {
//        Entity entityAssigned;
//        entityAssigned = entityOrigin;
//        weak_component<ComponentA> assignedComponentA = entityAssigned.get<ComponentA>();
//        CHECK_EQUAL(5, assignedComponentA->a);
//        assignedComponentA->a = 20;
//        CHECK_EQUAL(20, assignedComponentA->a);
//    }
//
//    CHECK_EQUAL(5, entityOrigin.get<ComponentA>()->a);
//}
//
SCENARIO("Entities copy control")
{
    GIVEN("An entity with a component")
    {
        Entity entityOrigin;
        entityOrigin.addComponent<ComponentA>(5);

        REQUIRE(entityOrigin.get<ComponentA>()->a == 5);

        GIVEN("A copy-construction of this entity")
        {
            Entity entityCopy(entityOrigin);
            REQUIRE(entityCopy.get<ComponentA>()->a == 5);

            WHEN("The copy's component is modified")
            {
                entityCopy.get<ComponentA>()->a =10;
                REQUIRE(entityCopy.get<ComponentA>()->a == 10);

                THEN("The source's component is not modified")
                {
                    REQUIRE(entityOrigin.get<ComponentA>()->a == 5);
                }
            }
        }

        GIVEN("A copy of this entity")
        {
            Entity entityCopy=entityOrigin;
            REQUIRE(entityCopy.get<ComponentA>()->a == 5);

            WHEN("The copy's component is modified")
            {
                entityCopy.get<ComponentA>()->a =20;
                REQUIRE(entityCopy.get<ComponentA>()->a == 20);

                THEN("The source's component is not modified")
                {
                    REQUIRE(entityOrigin.get<ComponentA>()->a == 5);
                }
            }
        }

        GIVEN("An assignment of this entity")
        {
            Entity entityCopy;
            entityCopy=entityOrigin;
            REQUIRE(entityCopy.get<ComponentA>()->a == 5);

            WHEN("The copy's component is modified")
            {
                entityCopy.get<ComponentA>()->a =30;
                REQUIRE(entityCopy.get<ComponentA>()->a == 30);

                THEN("The source's component is not modified")
                {
                    REQUIRE(entityOrigin.get<ComponentA>()->a == 5);
                }
            }
        }
    }
}

SCENARIO("Adding entities")
{
    GIVEN("A default constructed Manager and an Archetype")
    {
        Engine engine;

        Nodes nodesA_before = &engine.getNodes<ArchetypeA>();
        REQUIRE(nodesA_before->size() == 0);

        WHEN("An Entity matching this Archetype is added to the Manager")
        {
            Entity entity;
            entity.addComponent<ComponentA>(5);
            engine.addEntity(entity);

            THEN("The Nodes for the Archetype grows by one")
            {
                Nodes nodesA_after = &engine.getNodes<ArchetypeA>();
                REQUIRE(nodesA_after->size() == 1);

                THEN("Nodes type have reference semantic")
                {
                    REQUIRE(nodesA_before == nodesA_after);
                }
            }
        }
    }
}


SCENARIO("Removing entities")
{
    GIVEN("A Manager with one Entity")
    {
        Engine engine;

        Entity entity;
        entity.addComponent<ComponentA>(5);
        weak_entity firstEntity = engine.addEntity(entity);

        Nodes nodesA = &engine.getNodes<ArchetypeA>();
        REQUIRE(nodesA->size() == 1);

        WHEN("The Entity is removed")
        {
            engine.removeEntity(firstEntity);

            THEN("The entity is not accessible in the Nodes anymore")
            {
                REQUIRE(nodesA->size() == 0);
            }
        }
    }
}
