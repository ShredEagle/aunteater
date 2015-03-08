#ifndef _IDG_AE_CommonComponents
#define _IDG_AE_CommonComponents

#include <aunteater/Component.h>

class ComponentA : public aunteater::Component
{
public:
    ComponentA(int aInteger):
            a(aInteger)
    {}
    
    int a;

private:
    virtual aunteater::own_component<> clone_impl() const override
    {   return std::make_unique<ComponentA>(*this);  }
};

class ComponentB : public aunteater::Component
{
public:
    ComponentB(double aValue):
            b(aValue)
    {}
    
    double b;

private:
    virtual aunteater::own_component<> clone_impl() const override
    {   return std::make_unique<ComponentB>(*this);  }
};

class ArchetypeA
{
public:
    // defined in Entities.cpp
    static const aunteater::ArchetypeTypeSet gComponentTypes;
};

// defined in Entities.cpp
static const aunteater::ArchetypeTypeSet gArchetypeB{ &typeid(ComponentB) };
static const aunteater::ArchetypeTypeSet gArchetypeAnB{ &typeid(ComponentA), &typeid(ComponentB) };
#endif // #ifdef