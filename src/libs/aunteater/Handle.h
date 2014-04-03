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
        
        bool operator< (const Handle &aRhs) const
        {
            return mIndex < aRhs.mIndex;
        }
        
    private:
        T_index mIndex;
    };
    
} // namespace aunteater

#endif  // #ifdef