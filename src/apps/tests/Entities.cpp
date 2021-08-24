#include "CommonComponents.h"

#include "catch.hpp"

#include <aunteater/EntityManager.h>

using namespace aunteater;

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
            entity.add<ComponentB>(3.14);
            THEN("It contains the component, but not another")
            {
                REQUIRE_FALSE(entity.has<ComponentA>());
                REQUIRE(entity.has<ComponentB>());
                REQUIRE(3.14 == entity.get<ComponentB>().b);
            }

            WHEN("Adding the same component")
            {
                entity.add<ComponentB>(900000000.);
                THEN("The Component is replaced")
                {
                    REQUIRE(900000000. == entity.get<ComponentB>().b);
                }
            }

            WHEN("Removing the Component from the Entity")
            {
                entity.remove<ComponentB>();
                THEN("It does not contain any component anymore")
                {
                    REQUIRE_FALSE(entity.has<ComponentA>());
                    REQUIRE_FALSE(entity.has<ComponentB>());
                }
            }
        }
    }
}


SCENARIO("Entities copy control")
{
    GIVEN("An entity with a component")
    {
        Entity entityOrigin;
        entityOrigin.add<ComponentA>(5);

        REQUIRE(entityOrigin.get<ComponentA>().a == 5);

        GIVEN("A copy-construction of this entity")
        {
            Entity entityCopy(entityOrigin);
            REQUIRE(entityCopy.get<ComponentA>().a == 5);

            WHEN("The copy's component is modified")
            {
                entityCopy.get<ComponentA>().a =10;
                REQUIRE(entityCopy.get<ComponentA>().a == 10);

                THEN("The source's component is not modified")
                {
                    REQUIRE(entityOrigin.get<ComponentA>().a == 5);
                }
            }
        }

        GIVEN("A copy of this entity")
        {
            Entity entityCopy=entityOrigin;
            REQUIRE(entityCopy.get<ComponentA>().a == 5);

            WHEN("The copy's component is modified")
            {
                entityCopy.get<ComponentA>().a =20;
                REQUIRE(entityCopy.get<ComponentA>().a == 20);

                THEN("The source's component is not modified")
                {
                    REQUIRE(entityOrigin.get<ComponentA>().a == 5);
                }
            }
        }

        GIVEN("An assignment of this entity")
        {
            Entity entityCopy;
            entityCopy=entityOrigin;
            REQUIRE(entityCopy.get<ComponentA>().a == 5);

            WHEN("The copy's component is modified")
            {
                entityCopy.get<ComponentA>().a =30;
                REQUIRE(entityCopy.get<ComponentA>().a == 30);

                THEN("The source's component is not modified")
                {
                    REQUIRE(entityOrigin.get<ComponentA>().a == 5);
                }
            }
        }
    }
}


SCENARIO("Adding entities")
{
    GIVEN("A default constructed Manager and an Archetype")
    {
        EntityManager entityManager;

        Family & nodesA_before = entityManager.getFamily<ArchetypeA>();
        REQUIRE(nodesA_before.size() == 0);

        WHEN("An Entity matching this Archetype is added to the Manager")
        {
            Entity entity;
            entity.add<ComponentA>(5);
            entityManager.addEntity(entity);

            THEN("The Nodes for the Archetype grows by one")
            {
                Family & nodesA_after = entityManager.getFamily<ArchetypeA>();
                REQUIRE(nodesA_after.size() == 1);

                THEN("Families have reference semantic")
                {
                    REQUIRE(std::equal(nodesA_before.begin(), nodesA_before.end(),
                                       nodesA_after.begin(), nodesA_after.end()));
                }
            }
        }
    }
}


SCENARIO("Removing entities")
{
    GIVEN("A Manager with one Entity")
    {
        EntityManager entityManager;

        Entity entity;
        entity.add<ComponentA>(5);
        weak_entity firstEntity = entityManager.addEntity(entity);

        Family & nodesA = entityManager.getFamily<ArchetypeA>();
        REQUIRE(nodesA.size() == 1);

        WHEN("The Entity is removed")
        {
            entityManager.markToRemove(firstEntity);
            entityManager.update(Timer{});

            THEN("The entity is not accessible in the Nodes anymore")
            {
                REQUIRE(nodesA.size() == 0);
            }
        }
    }
}
