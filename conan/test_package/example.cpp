#include <aunteater/Engine.h>

#include <cstdlib>


int main()
{
    aunteater::Engine engine;
    engine.addEntity("goodname", aunteater::Entity{});
    return EXIT_SUCCESS;
}
