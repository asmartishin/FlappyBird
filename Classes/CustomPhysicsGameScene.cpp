#include "CustomPhysicsGameScene.h"

using namespace cocos2d;

namespace NFlappyBird {
    Scene *TCustomPhysicsGameScene::createScene() {
        auto scene = Scene::createWithPhysics();
        scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

        auto layer = TCustomPhysicsGameScene::create();

        scene->addChild(layer);

        return scene;
    }

    bool TCustomPhysicsGameScene::init() {
        if (!Layer::init()) {
            return false;
        }

        TAbstractGameScene::init();

        SpawnBird();

        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->onTouchBegan = CC_CALLBACK_2(TCustomPhysicsGameScene::OnTouchBegin, this);
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

        return true;
    }

    void TCustomPhysicsGameScene::SpawnBird() {
        Bird.reset(new TBirdCustom(WindowSize));

        auto node = Bird->Spawn({WindowSize.width * BIRD_HORIZONTAL_OFFSET, WindowSize.height * BIRD_VERTICAL_OFFSET});
        addChild(node);
    }

    bool TCustomPhysicsGameScene::OnTouchBegin(Touch *touch, Event *event) {
        BirdStartFlying();
        scheduleOnce(schedule_selector(TCustomPhysicsGameScene::BirdStopFlying), BIRD_FLY_DURATION);

        return true;
    }

    void TCustomPhysicsGameScene::BirdStartFlying() {
        Bird->StartFlying();
    }

    void TCustomPhysicsGameScene::BirdStopFlying(float dt) {
        Bird->StopFlying();
    }

    void TCustomPhysicsGameScene::update(float dt) {
        Bird->Fly();
    }

    void TCustomPhysicsGameScene::Restart() {
        auto scene = TCustomPhysicsGameScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
}
