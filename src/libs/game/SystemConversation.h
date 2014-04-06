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

#include <boost/property_tree/ptree.hpp>

class SystemConversation : public aunteater::System
{
public:
    SystemConversation(aunteater::Engine &aEngine,
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
    boost::property_tree::ptree mInitialTree;
    boost::property_tree::ptree mConversationTree;
};

#endif /* defined(__aunteater__SystemConversation__) */
