#include <aunteater/Entity.h>
#include <aunteater/EntityManager.h>

#include <cstdlib>


int main()
{
    aunteater::EntityManager entityManager;
    entityManager.addEntity("goodname", aunteater::Entity{});
    return EXIT_SUCCESS;
}
