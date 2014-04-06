//
//  SystemConversation.h
//  aunteater
//
//  Created by Adrien on 05/04/14.
//
//

#ifndef __aunteater__SystemConversation__
#define __aunteater__SystemConversation__

#include <aunteater/System.h>
#include <aunteater/Engine.h>

#include <Polycode.h>
#include <boost/property_tree/ptree.hpp>

class SystemConversation : public aunteater::System
{
public:
    SystemConversation(aunteater::Engine &aEngine,
                       Polycode::Screen *aScreen,
                       const std::string &aInitialDoc,
                       const std::string &aConversationDoc);
    
    virtual void addedToEngine(aunteater::Engine &aEngine);
    
    virtual void update(float time);
    
protected:
    std::string stateKey(aunteater::Node &aInitiatorNode);
    
private:
    aunteater::Nodes mPlayers;
    aunteater::Nodes mPNJs;
    
    aunteater::Engine &mEngine;
    
    Polycode::Screen *mScreen;
    
    boost::property_tree::ptree mInitialTree;
    boost::property_tree::ptree mConversationTree;
};

#endif /* defined(__aunteater__SystemConversation__) */
