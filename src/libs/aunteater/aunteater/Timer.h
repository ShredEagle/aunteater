#pragma once


namespace aunteater {


// TODO move to handy when it is made into a separate repo
template <class T_representation>
class Timer_base
{
public:
    using Value_t = T_representation;

    Timer_base() = default;

    explicit Timer_base(Value_t aInitialTime) :
        mTime{aInitialTime}
    {}

    void mark(Value_t aMonotonic)
    {
        mDelta = aMonotonic - mTime;
        mTime = aMonotonic;
    }

    Value_t simulationTime() const
    {
        return mTime;
    }

    Value_t delta() const
    {
        return mDelta;
    }

private:
    Value_t mTime{0};
    Value_t mDelta{0};
};


using Timer = Timer_base<double>;


} // namespace aunteater
