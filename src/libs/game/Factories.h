//
//  Factories.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__Factories__
#define __aunteater__Factories__

#define BASE_PATH "/Users/adn/GDJ/"

#include "Entity.h"

namespace Polycode
{
    class Screen;
}

aunteater::Entity createPlayer(Polycode::Screen *aScreen);

#endif /* defined(__aunteater__Factories__) */
