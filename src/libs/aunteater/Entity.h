#ifndef _IDG_AE_Entity
#define _IDG_AE_Entity

#include <map>

namespace aunteater
{
    
    class Component;
    
    class Entity
    {
    public:
        /// \brief Adds a component
        void addComponent(std::shared_ptr<Component> aComponent);
        void removeComponent(const std::type_info & aComponentId);
        
    private:
        std::map<const std::type_info *, std::shared_ptr<Component> > mComponents;
    };
    
} // namespace aunteater

#endif  // #ifdef