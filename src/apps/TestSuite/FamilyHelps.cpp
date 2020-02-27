#include "catch.hpp"

#include "CommonComponents.h"

#include <aunteater/Engine.h>
#include <aunteater/FamilyHelp.h>

using namespace aunteater;

SCENARIO("FamilyHelp usage")
{
    GIVEN("An Engine with FamilyHelp for ArchetypeA")
    {
        Engine engine;
        FamilyHelp<ArchetypeA> help{engine};
        REQUIRE(help.size() == 0);

        WHEN("Entites are added matching the archetype")
        {
            weak_entity entity1 = engine.addEntity(Entity().add<ComponentA>(10));
            weak_entity entity2 = engine.addEntity(Entity().add<ComponentA>(11));

            REQUIRE(entity1->get<ComponentA>().a == 10);
            REQUIRE(entity2->get<ComponentA>().a == 11);

            THEN("The FamilyHelp size increase accordingly")
            {
                REQUIRE(help.size() == 2);
            }

            THEN("The FamilyHelp can be iterated")
            {
                std::size_t counter = 0;
                for(const auto & node : help)
                {
                    ++counter;
                }
                REQUIRE(counter == 2);
            }

            THEN("The FamilyHelp iteratee provides structured binding via copy")
            {
                std::vector<ComponentA> copies;
                for(auto [compA] : help)
                {
                    copies.push_back(compA);
                    // Should modify a copy, not the component from the entity
                    compA.a = 0;
                }

                REQUIRE(std::vector<ComponentA>{ {10}, {11} } == copies);
                REQUIRE(entity1->get<ComponentA>().a == 10);
                REQUIRE(entity2->get<ComponentA>().a == 11);
            }

            THEN("The FamilyHelp iteratee provides structured binding via const copy")
            {
                std::vector<ComponentA> copies;
                for(const auto [compA] : help)
                {
                    copies.push_back(compA);
                }

                REQUIRE(std::vector<ComponentA>{ {10}, {11} } == copies);
            }

            THEN("The FamilyHelp iteratee provides structured binding via const reference")
            {
                std::vector<ComponentA> copies;
                for(const auto & [compA] : help)
                {
                    copies.push_back(compA);
                }

                REQUIRE(std::vector<ComponentA>{ {10}, {11} } == copies);
            }

            THEN("The FamilyHelp structured binding via reference allows modifying the component")
            {
                for(auto & [compA] : help)
                {
                    ++compA.a;
                }

                REQUIRE(entity1->get<ComponentA>().a == 11);
                REQUIRE(entity2->get<ComponentA>().a == 12);
            }

            THEN("The FamilyHelp const iteration provides structued binding")
            {
                auto first = help.cbegin();
                {
                    // Via const reference
                    const auto & [compA] = first++;
                    REQUIRE(compA.a == 10);
                }

                {
                    // Via copy
                    auto [compA] = first++;
                    REQUIRE(compA.a == 11);
                }

                REQUIRE(first == help.cend());
            }

            GIVEN("A constant FamilyHelp for ArchetypeA")
            {
                const FamilyHelp<ArchetypeA> constHelp{engine};

                THEN("The constant FamilyHelp has the correct size")
                {
                    REQUIRE(constHelp.size() == 2);
                }

                THEN("The constant FamilyHelp iteration provides structured binding")
                {
                    std::vector<ComponentA> copies;
                    for(auto & [compA] : constHelp)
                    {
                        copies.push_back(compA);
                        compA.a = 0;
                    }

                    REQUIRE(std::vector<ComponentA>{ {10}, {11} } == copies);
                    // The component itself gets modified:
                    // Family and FamilyHelp are a reference type, making them const does not make
                    // the refered type const
                    REQUIRE(entity1->get<ComponentA>().a == 0);
                    REQUIRE(entity2->get<ComponentA>().a == 0);
                }
            }
        }

    }
}
