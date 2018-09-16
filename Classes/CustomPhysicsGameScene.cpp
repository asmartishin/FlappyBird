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

        Pipes = {
            std::unique_ptr<TPipe>(new TTopPipe(WindowSize)),
            std::unique_ptr<TPipe>(new TBottomPipe(WindowSize)),
            std::unique_ptr<TPipe>(new TTarget(WindowSize))
        };

        SpawnEdge();
        SpawnBird();

        schedule(schedule_selector(TCustomPhysicsGameScene::SpawnPipes), PIPE_SPAWN_FREQUENCY);

        auto contactListener = EventListenerPhysicsContact::create();
        contactListener->onContactBegin = CC_CALLBACK_1(TCustomPhysicsGameScene::OnContactBegin, this);
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = CC_CALLBACK_2(TCustomPhysicsGameScene::OnTouchBegin, this);
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

        return true;
    }

    void TCustomPhysicsGameScene::SpawnBird() {
        Bird.reset(new TBird(WindowSize));

        auto node = Bird->Spawn({WindowSize.width * BIRD_HORIZONTAL_OFFSET, WindowSize.height * BIRD_VERTICAL_OFFSET});
        addChild(node);
    }

    void TCustomPhysicsGameScene::SpawnEdge() {
        Edge.reset(new TEdge(WindowSize));

        auto node = Edge->Spawn({WindowSize.width / 2, WindowSize.height / 2});
        addChild(node);
    }

    void TCustomPhysicsGameScene::SpawnPipes(float dt) {
        auto gapRatio = random(0.f, 1.f - GAP_HEIGHT);

        for (const auto& pipe: Pipes) {
            auto node = pipe->Spawn({WindowSize.width, WindowSize.height * gapRatio});

            addChild(node);

            node->runAction(Sequence::create(
                MoveTo::create(PIPE_MOVE_SPEED, {-WindowSize.width * (1 + PIPE_WIDTH), node->getPosition().y}),
                RemoveSelf::create(),
                nullptr)
            );
        }
    }

    bool TCustomPhysicsGameScene::OnContactBegin(PhysicsContact &contact) {
        auto firstNodeBitmask = contact.getShapeA()->getBody()->getCategoryBitmask();
        auto secondNodeBitmask = contact.getShapeB()->getBody()->getCategoryBitmask();

        if (
            firstNodeBitmask != static_cast<int>(EPhysicsCategory::Obstacle) &&
            secondNodeBitmask != static_cast<int>(EPhysicsCategory::Obstacle)
            ) {
            ++Score;
            ScoreLabel->setString(toString<size_t>(Score));
        } else {
            auto scene = TCustomPhysicsGameScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
        }

        return true;
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
}
