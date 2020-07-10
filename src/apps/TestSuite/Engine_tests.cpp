#include "catch.hpp"

#include <aunteater/Engine.h>

using namespace aunteater;


// Chained component
class ComponentList : public aunteater::Component<ComponentList>
{
public:
    ComponentList(weak_entity aNext = nullptr):
        next{aNext}
    {}

    weak_entity next;
};


// FamilyObserver recursively deleting entities in the ComponentList chain
class RecursiveRemover : public FamilyObserver
{
public:
    RecursiveRemover(Engine & aEngine) :
        engine(aEngine)
    {}

    void addedEntity(LiveEntity &aEntity) override
    {}

    void removedEntity(LiveEntity &aEntity) override
    {
        for(auto next = aEntity.get<ComponentList>().next;
            next != nullptr;
            next = next->get<ComponentList>().next)
        {
            engine.markToRemove(next);
        }
    }

    Engine & engine;
};


SCENARIO("Nested entities removal")
{
    GIVEN("A Family of chained components and an observer recursively deleting entities")
    {
        Engine engine;
        Family & listFamily = engine.getFamily<Archetype<ComponentList>>();

        REQUIRE(engine.countEntities() == 0);
        REQUIRE(listFamily.size() == 0);

        RecursiveRemover remover{engine};
        listFamily.registerObserver(&remover);

        weak_entity a = engine.addEntity(Entity{}.add<ComponentList>());
        weak_entity b = engine.addEntity(Entity{}.add<ComponentList>());

        REQUIRE(engine.countEntities() == 2);
        REQUIRE(listFamily.size() == 2);

        weak_entity min = std::min(a, b);
        weak_entity max = std::max(a, b);

        WHEN("The entities are chained in increasing address order")
        {
            min->get<ComponentList>().next = max;

            // Sanity check
            engine.update(Timer{});
            REQUIRE(listFamily.size() == 2);

            WHEN("The tail is removed")
            {
                engine.markToRemove(max);
                // Sanity check
                REQUIRE(listFamily.size() == 2);

                engine.update(Timer{});

                THEN("The tail has been removed from the family")
                {
                    REQUIRE(listFamily.size() == 1);
                }
                THEN("The tail has been removed from the engine")
                {
                    REQUIRE(engine.countEntities() == 1);
                }
            }

            WHEN("The root is removed")
            {
                engine.markToRemove(min);
                engine.update(Timer{});

                THEN("Both head and tail have been removed from the family")
                {
                    REQUIRE(listFamily.size() == 0);
                }
                THEN("Both head and tail have been removed from the engine")
                {
                    REQUIRE(engine.countEntities() == 0);
                }
            }
        }

        WHEN("The entities are chained in decreasing address order")
        {
            max->get<ComponentList>().next = min;

            WHEN("The tail is removed")
            {
                engine.markToRemove(min);
                engine.update(Timer{});

                THEN("The tail has been removed from the family")
                {
                    REQUIRE(listFamily.size() == 1);
                }
                THEN("The tail has been removed from the engine")
                {
                    REQUIRE(engine.countEntities() == 1);
                }
            }

            WHEN("The root is removed")
            {
                engine.markToRemove(max);
                engine.update(Timer{});

                THEN("Both head and tail have been removed from the family")
                {
                    // Note: this statement is the one motivating this whole scenario:
                    // with the initial approach were marking entity for removal insert them in a set later iterated
                    // nested removal could fail depending on the relative position in the set
                    // (position of the currently removed entity vs the position of the entity it is recursively marking for removal)
                    REQUIRE(listFamily.size() == 0);
                }
                THEN("Both head and tail have been removed from the engine")
                {
                    REQUIRE(engine.countEntities() == 0);
                }
            }
        }
    }
}
