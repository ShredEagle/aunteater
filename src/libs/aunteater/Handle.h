#ifndef _IDG_AE_Handle
#define _IDG_AE_Handle

namespace aunteater
{
    
    template <class T, class T_index=size_t>
    class Handle
    {
    public:
        Handle(T_index aIndex):
                mIndex(aIndex)
        {}
        
        T_index get()
        {
            return mIndex;
        }
       
        // Not possible without a reference to the container instance.
//        T & operator*()
//        {
//            return
//        }
        
        template <class T_container>
        T & deref(T_container &aContainer)
        {
            return aContainer.at(mIndex);
        }
        
        bool operator< (const Handle &aRhs) const
        {
            return mIndex < aRhs.mIndex;
        }
        
    private:
        T_index mIndex;
    };
    
} // namespace aunteater

#endif  // #ifdef