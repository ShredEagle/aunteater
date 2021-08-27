#pragma once


#include "EntityManager.h"
#include "Timer.h"
#include "System.h"

#include <memory> 
#include <vector>


namespace aunteater {


namespace detail {

    /// \brief Provide the member type "VT_inputState" if the pack has 1 type, or "void" if it has 0.
    template <class ... VT_inputState>
    struct InputState;

    template <class T_actualState>
    struct InputState<T_actualState>
    {
        using type = T_actualState;
    };

    template <>
    struct InputState<>
    {
        using type = void;
    };

    /// \brief Convenience alias to InputState<>::type
    template <class ... VT_inputState>
    using InputState_t = typename InputState<VT_inputState...>::type;



    template <class ... VT_inputState>
    struct DefaultUpdater
    {
        void start()
        {}
        void finish()
        {}

        void operator()(System<InputState_t<VT_inputState...>> & aSystem, const Timer aTime, const VT_inputState & ... vaInputState)
        {
            aSystem.update(aTime, vaInputState...);
        }
    };

} // namespace detail


template <class ... VT_inputState>
class SystemManager
{
    static_assert(sizeof...(VT_inputState) < 2, "Only 0 or 1 custom input state classes are allowed.");

    using System_t = System<detail::InputState_t<VT_inputState...>>;

public:
    SystemManager(EntityManager & aEntityManager);

    /// \brief Instantiate and add a system of class T_system.
    ///
    ///  Provides entityManager reference as 1st ctor argument, forwards aArgs as following arguments.
    template <class T_system, class... VT_ctorArgs>
    std::shared_ptr<T_system> add(VT_ctorArgs &&... aArgs);

    void add(std::shared_ptr<System_t> aSystem);
    // TODO
    // removeSystem

    template <class T_updater = detail::DefaultUpdater<VT_inputState...>>
    void update(const Timer aTime,
                const VT_inputState & ... vaInputState,
                // Note: this is not accepted by MSVC, pretending there is no default constructor for the type
                // so use an overload instead (where MSVC happily finds the default ctor, all of a sudden)
                //T_updater && aUpdater = detail::DefaultUpdater<VT_inputState...>{});
                T_updater && aUpdater);

    void update(const Timer aTime, const VT_inputState & ... vaInputState)
    { update(aTime, vaInputState..., detail::DefaultUpdater<VT_inputState...>{}); }

    /// \return The pause state before the call
    bool isPaused();
    /// \return The pause state before the call
    bool pause(bool aPauseMode);

private:
    EntityManager & mEntityManager;
    std::vector<std::shared_ptr<System_t>> mSystems;
    bool mPaused{false};
};


//
// Implementations
//
template <class ... VT_inputState>
SystemManager<VT_inputState ...>::SystemManager(EntityManager & aEntityManager) :
    mEntityManager{aEntityManager}
{}


template <class ... VT_inputState>
template <class T_system, class... VT_ctorArgs>
std::shared_ptr<T_system> SystemManager<VT_inputState ...>::add(VT_ctorArgs && ... aArgs)
{
    auto result = std::make_shared<T_system>(mEntityManager, std::forward<VT_ctorArgs>(aArgs)...);
    add(result);
    return result;
}


template <class ... VT_inputState>
void SystemManager<VT_inputState ...>::add(std::shared_ptr<System_t> aSystem)
{
    mSystems.push_back(std::move(aSystem));
}


template <class ... VT_inputState>
template <class T_updater>
void SystemManager<VT_inputState ...>::update(const Timer aTime,
                                              const VT_inputState & ... vaInputState,
                                              T_updater && aUpdater)
{
    if (isPaused())
    {
        return;
    }

    aUpdater.start();

    for (auto & system : mSystems)
    {
        aUpdater(*system, aTime, vaInputState...);
    }
    mEntityManager.removeComponents();
    mEntityManager.removeEntities();

    aUpdater.finish();
}


template <class ... VT_inputState>
bool SystemManager<VT_inputState ...>::isPaused()
{
    return mPaused;
}


template <class ... VT_inputState>
bool SystemManager<VT_inputState ...>::pause(bool aPauseMode)
{
    bool result = isPaused();
    mPaused = aPauseMode;
    return result;
}


} // namespace aunteater
