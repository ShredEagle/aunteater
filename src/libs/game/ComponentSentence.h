//
//  ComponentSentence.h
//  aunteater
//
//  Created by Adrien on 06/04/14.
//
//

#ifndef aunteater_ComponentSentence_h
#define aunteater_ComponentSentence_h

#include <aunteater/Component.h>

#include <string>

class ComponentSentence : public aunteater::Component
{
public:
    ComponentSentence() : Component()
    {}
    
    std::string identifier;
    
};


#endif
