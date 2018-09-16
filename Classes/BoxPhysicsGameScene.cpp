#include "BoxPhysicsGameScene.h"

using namespace cocos2d;

namespace NFlappyBird {
    Scene *TBoxPhysicsGameScene::createScene() {
        auto scene = Scene::createWithPhysics();
        scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

        auto layer = TBoxPhysicsGameScene::create();

        scene->addChild(layer);

        return scene;
    }

    bool TBoxPhysicsGameScene::init() {
        if (!Layer::init()) {
            return false;
        }

        TAbstractGameScene::init();

        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

        b2Vec2 gravity = b2Vec2(0.0f, BOX_GRAVITY);
        World.reset(new b2World(gravity));

        SpawnBird();

        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->onTouchBegan = CC_CALLBACK_2(TBoxPhysicsGameScene::OnTouchBegin, this);
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

        return true;
    }

    void TBoxPhysicsGameScene::update(float dt) {
        World->Step(dt, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

        for (auto body = World->GetBodyList(); body != nullptr; body = body->GetNext())
            if (body->GetUserData()) {
                auto node = static_cast<Node*>(body->GetUserData());
                node->setPosition({body->GetPosition().x * BOX_SCALE_RATIO, body->GetPosition().y * BOX_SCALE_RATIO});
            }
        World->ClearForces();
    }

    bool TBoxPhysicsGameScene::OnTouchBegin(cocos2d::Touch *touch, cocos2d::Event *event) {
        Bird->Fly();

        return true;
    }

    void TBoxPhysicsGameScene::SpawnBird() {
        Bird.reset(new TBirdBox(WindowSize, World.get()));

        auto node = Bird->Spawn({WindowSize.width * BIRD_HORIZONTAL_OFFSET, WindowSize.height * BIRD_VERTICAL_OFFSET});
        addChild(node);
    }

    void TBoxPhysicsGameScene::Restart() {
        auto scene = TBoxPhysicsGameScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
}