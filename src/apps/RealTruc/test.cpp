#include "test.h"		

Test::Test(Polycode::PolycodeView *view) : core(NULL), scene(NULL) {

		core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);
        CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_NEAREST);

		Screen *screen = new Screen();
		
		penis = new ScreenSprite("../300coin.png",300,300);
		
		penis->setPosition(200,200);
		screen->addChild(penis);

		penis->addAnimation("ExampleAnimation", "0,1", 0.3);
		penis->playAnimation("ExampleAnimation", 0, false);

}

Test::~Test() {
        delete scene;
        delete core;
}

bool Test::Update() {
    return core->updateAndRender();
}