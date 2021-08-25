#include "catch.hpp"


#include <aunteater/EntityManager.h>
#include <aunteater/FamilyHelp.h>
#include <aunteater/SystemManager.h>


using namespace aunteater;


struct CustomInput
{
    int value;
};

using BaseEntity = Archetype<>;

struct InputChecker : public System<CustomInput>
{
    InputChecker(EntityManager & aEntityManager) :
        mEntities{aEntityManager}
    {}

    void update(const Timer aTime, const CustomInput & aInputState) override
    {
        read = aInputState.value;
    }

    int read{0};
    const aunteater::FamilyHelp<BaseEntity> mEntities;
};

SCENARIO("Systems accepting a custom input state type.")
{
    GIVEN("Entity and System managers.")
    {
        EntityManager entityManager;
        SystemManager<CustomInput> systemManager{entityManager};

        entityManager.addEntity(Entity{});
        std::shared_ptr<InputChecker> system = systemManager.add<InputChecker>();

        WHEN("The systems are updated, providing the custom input state")
        {
            CustomInput input{18};
            systemManager.update(Timer{}, input);

            THEN("The systems update can read provided input state")
            {
                REQUIRE(system->read == 18);
            }
        }
    }
}
