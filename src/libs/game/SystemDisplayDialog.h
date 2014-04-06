//
//  SystemDisplayDialog.h
//  aunteater
//
//  Created by Adrien on 06/04/14.
//
//

#ifndef __aunteater__SystemDisplayDialog__
#define __aunteater__SystemDisplayDialog__

#include <aunteater/System.h>
#include <aunteater/Engine.h>


class SystemDisplayDialog : public aunteater::System
{
public:
    SystemDisplayDialog(aunteater::Engine &aEngine);
    
    virtual void addedToEngine(aunteater::Engine &aEngine);
    
    virtual void update(float time);
    
private:
    aunteater::Nodes mDialogs;
    aunteater::Engine & mEngine;
};

#endif /* defined(__aunteater__SystemDisplayDialog__) */
