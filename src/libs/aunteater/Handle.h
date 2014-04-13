#ifndef _IDG_AE_Handle
#define _IDG_AE_Handle

#include <vector>

namespace aunteater
{
    
    /// \todo This is an abomination to hardcode a default type, but the handle has to be
    /// profoundly redesigned
    template <class T_object, class T_container=std::vector<T_object>, class T_index=size_t>
    class Handle
    {
    public:
        Handle(T_container &aContainer, T_index aIndex):
                mContainer(&aContainer),
                mIndex(aIndex)
        {}
        
        T_index get()
        {
            return mIndex;
        }
       
        // Not possible without a reference to the container instance.
        T_object & operator*()
        {
            return mContainer->at(mIndex);
        }
        
        T_object * operator->()
        {
            return &(this->operator*());
        }
        
        template <class T_contr>
        T_object & deref(T_contr &aContainer)
        {
            return aContainer.at(mIndex);
        }
        
        bool operator< (const Handle &aRhs) const
        {
            return mIndex < aRhs.mIndex;
        }
        
        bool operator==(const Handle &aRhs) const
        {
            return (mContainer == aRhs.mContainer) && (mIndex == aRhs.mIndex);
        }
        
        bool operator!=(const Handle &aRhs) const
        {
            return !(*this == aRhs);
        }
        
    private:
        // We need the object to be assignable, cannot use reference here
        T_container *mContainer;
        T_index mIndex;
    };
    
    template <class T_container, class T_index>
    Handle<typename T_container::value_type, T_container, T_index> makeHandle(T_container &aContainer,
                                                                              T_index aIndex)
    {
        return Handle<typename T_container::value_type, T_container, T_index>(aContainer, aIndex);
    }
    
} // namespace aunteater

#endif  // #ifdef