#ifndef _IDG_AE_Entity
#define _IDG_AE_Entity

#include <map>
#include <memory>

namespace aunteater
{
    
    class Component;
    
    class Entity
    {
    public:
        /// \brief Adds a component
        void addComponent(std::shared_ptr<Component> aComponent);
        void removeComponent(const std::type_info & aComponentId);
        
        bool has(const std::type_info *aComponentId)
        {
            return mComponents.count(aComponentId);
        }
        
        /// Undefined behavior if aComponentId is not a key in the map.
        /// \todo We do not want to actually share ownership, rewrite with weak or something
        std::shared_ptr<Component> get(const std::type_info *aComponentId)
        {
            return mComponents.find(aComponentId)->second;
        }
        
    private:
        std::map<const std::type_info *, std::shared_ptr<Component> > mComponents;
    };
    
} // namespace aunteater

#endif  // #ifdef