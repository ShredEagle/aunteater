#pragma once


namespace aunteater {


// TODO move to handy when it is made into a separate repo
template <class T_representation>
class Timer_base
{
public:
    Timer_base() = default;

    explicit Timer_base(T_representation aInitialTime) :
        mTime{aInitialTime}
    {}

    void mark(T_representation aMonotonic)
    {
        mDelta = aMonotonic - mTime;
        mTime = aMonotonic;
    }

    T_representation simulationTime() const
    {
        return mTime;
    }

    T_representation delta() const
    {
        return mDelta;
    }

private:
    T_representation mTime{0};
    T_representation mDelta{0};
};


using Timer = Timer_base<double>;


} // namespace aunteater
