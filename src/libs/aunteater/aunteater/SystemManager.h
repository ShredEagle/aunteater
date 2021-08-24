#pragma once


#include "EntityManager.h"
#include "Timer.h"
#include "System.h"

#include <memory> 
#include <vector>


namespace aunteater {


template <class T>
constexpr bool always = std::is_same_v<T, T>;


template <class T_inputState>
struct DefaultUpdater
{
    void start()
    {}
    void finish()
    {}

    void operator()(System<T_inputState> & aSystem, const Timer aTime, const T_inputState & aInputState)
    {
        aSystem.update(aTime, aInputState);
    }
};

template <>
struct DefaultUpdater<void>
{
    void start()
    {}
    void finish()
    {}

    void operator()(System<void> & aSystem, const Timer aTime)
    {
        aSystem.update(aTime);
    }
};


template <class T_inputState = void>
class SystemManager
{
public:
    SystemManager(EntityManager & aEntityManager);

    /// \brief Instantiate and add a system of class T_system.
    ///
    ///  Provides entityManager reference as 1st ctor argument, forwards aArgs as following arguments.
    template <class T_system, class... VT_ctorArgs>
    std::shared_ptr<T_system> addSystem(VT_ctorArgs &&... aArgs);

    void addSystem(std::shared_ptr<System<T_inputState>> aSystem);
    // TODO
    // removeSystem

    //template <class T_updater>
    //std::enable_if_t<! std::is_same_v<void, T_inputState> && always<T_updater>>
    //update(EntityManager & aEntityManager, const Timer aTime, const T_inputState & aInputState,
    //       T_updater && aUpdater = DefaultUpdater<T_inputState>{});

    template <class T_updater = DefaultUpdater<T_inputState>>
    std::enable_if_t<std::is_same_v<void, T_inputState> && always<T_updater>>
    update(const Timer aTime, T_updater && aUpdater =  DefaultUpdater<T_inputState>{});


    /// \return The pause state before the call
    bool isPaused();
    /// \return The pause state before the call
    bool pause(bool aPauseMode);

private:
    EntityManager & mEntityManager;
    std::vector<std::shared_ptr<System<T_inputState>>> mSystems;
    bool mPaused{false};
};


//
// Implementations
//
template <class T_inputState>
SystemManager<T_inputState>::SystemManager(EntityManager & aEntityManager) :
    mEntityManager{aEntityManager}
{}


template <class T_inputState>
template <class T_system, class... VT_ctorArgs>
std::shared_ptr<T_system> SystemManager<T_inputState>::addSystem(VT_ctorArgs && ... aArgs)
{
    auto result = std::make_shared<T_system>(mEntityManager, std::forward<VT_ctorArgs>(aArgs)...);
    addSystem(result);
    return result;
}


template <class T_inputState>
void SystemManager<T_inputState>::addSystem(std::shared_ptr<System<T_inputState>> aSystem)
{
    mSystems.push_back(std::move(aSystem));
}


//template <class T_inputState>
//template <class T_updater>
//std::enable_if_t<std::is_same_v<void, T_inputState> && always<T_updater>>
//SystemManager<T_inputState>::update(EntityManager & aEntityManager, const Timer aTime, const T_inputState & aInputState, T_updater && aUpdater)
template <class T_inputState>
template <class T_updater>
std::enable_if_t<std::is_same_v<void, T_inputState> && always<T_updater>>
SystemManager<T_inputState>::update(const Timer aTime, T_updater && aUpdater)
{
    if (isPaused())
    {
        return;
    }

    aUpdater.start();

    for (auto & system : mSystems)
    {
        aUpdater(*system, aTime);
    }
    mEntityManager.removeEntities();

    aUpdater.finish();
}


//template <class T_inputState>
//void SystemManager<T_inputState>::update(EntityManager & aEntityManager, const Timer aTime, const T_inputState & aInputState)
//{
//    update(aTime, aInputState, DefaultUpdater{});
//}


template <class T_inputState>
bool SystemManager<T_inputState>::isPaused()
{
    return mPaused;
}


template <class T_inputState>
bool SystemManager<T_inputState>::pause(bool aPauseMode)
{
    bool result = isPaused();
    mPaused = aPauseMode;
    return result;
}


} // namespace aunteater
