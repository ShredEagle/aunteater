#include "Family.h"

using namespace aunteater;


void Family::addEntity(std::shared_ptr<Entity> aEntity)
{
    addIfMatch(aEntity);
}

void Family::removeEntity(std::shared_ptr<Entity> aEntity)
{
    removeIfMatch(aEntity);
}

void Family::componentAddedToEntity(std::shared_ptr<Entity> aEntity, <#std::type_info *aComponent#>)
{
    
}