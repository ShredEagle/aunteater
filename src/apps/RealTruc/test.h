#include <iostream>
#include <Polycode.h>
#include "PolycodeView.h"
#include "math.h"

class Test : public Polycode::EventHandler {
public:
    Test(Polycode::PolycodeView *view);
    ~Test();
    bool Update();

private:
        Polycode::Core *core;
        Polycode::Scene *scene;
		Polycode::ScreenSprite *penis;
};