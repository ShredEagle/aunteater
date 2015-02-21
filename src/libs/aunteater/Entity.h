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
        /// \deprecated Use template addComponent instead
        void addComponent(std::shared_ptr<Component> aComponent);

        /// \todo MAJOR for add and remove component, update the families !
        
        /// \todo Once the componet ownership problem is addressed
        /// return the component
        template <class T_component, class... Args>
        void addComponent(Args... aArgs)
        {
            addComponent(std::make_shared<T_component>(aArgs...));
        }
        
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
        
        template <class T_component>
        std::shared_ptr<T_component> get()
        {
            return std::static_pointer_cast<T_component>
                (mComponents.find(&typeid(T_component))->second);
        }
        
    private:
        std::map<const std::type_info *, std::shared_ptr<Component> > mComponents;
    };
    
} // namespace aunteater

#endif  // #ifdef