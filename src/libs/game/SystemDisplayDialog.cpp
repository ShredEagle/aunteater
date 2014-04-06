//
//  SystemDisplayDialog.cpp
//  aunteater
//
//  Created by Adrien on 06/04/14.
//
//

#include "SystemDisplayDialog.h"

#include "ComponentPosition.h"
#include "ComponentTextList.h"
#include "ComponentKeyboard.h"

using namespace aunteater;

class NodeDialog
{
public:
    static const ComponentIds gComponentTypes;
};

const ComponentIds NodeDialog::gComponentTypes = { &typeid(ComponentPosition),
                                                   &typeid(ComponentTextList),
                                                   &typeid(ComponentKeyboard),
};

SystemDisplayDialog::SystemDisplayDialog(Engine &aEngine) :
        mDialogs(aEngine.getNodes<NodeDialog>()),
        mEngine(aEngine)
{
    
    mEngine.addSystem(this);
}

void SystemDisplayDialog::addedToEngine(aunteater::Engine &aEngine)
{}
    
void SystemDisplayDialog::update(float time)
{
    for(auto & dialog : mDialogs)
    {
        auto & position = dialog.get<ComponentPosition>();
        auto & textlist = dialog.get<ComponentTextList>();
        
        textlist.rectangle->setPosition(position.x, position.y);
        
        
        Polycode::CoreInput * keyboard = Polycode::CoreServices::getInstance()->getCore()->getInput();
        
		if(keyboard->getKeyState(Polycode::KEY_KP1))
        {
            
        }
    }
}
 