#include "GameScene.h"

using namespace cocos2d;

namespace NFlappyBird {
    Scene *GameScene::createScene() {
        auto scene = Scene::createWithPhysics();
        scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

        auto layer = GameScene::create();

        scene->addChild(layer);

        return scene;
    }

    bool GameScene::init() {
        if (!Layer::init()) {
            return false;
        }

        auto director = Director::getInstance();

        director->setDisplayStats(false);
        WindowSize = director->getWinSize();
        Origin = director->getVisibleOrigin();

        Pipes = {
            std::unique_ptr<TPipe>(new TTopPipe(WindowSize)),
            std::unique_ptr<TPipe>(new TBottomPipe(WindowSize)),
            std::unique_ptr<TPipe>(new TTarget(WindowSize))
        };

        auto background = DrawNode::create();
        background->drawSolidRect(Origin, WindowSize, GAME_BACKGROUND_COLOR);
        addChild(background);

        SpawnScoreLabel();
        SpawnMenu();
        SpawnEdge();
        SpawnBird();

        srand(static_cast<unsigned int>(time(nullptr)));
        schedule(schedule_selector(GameScene::SpawnPipes), PIPE_SPAWN_FREQUENCY);

        auto contactListener = EventListenerPhysicsContact::create();
        contactListener->onContactBegin = CC_CALLBACK_1(GameScene::OnContactBegin, this);
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::OnTouchBegin, this);
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

        scheduleUpdate();

        return true;
    }

    void GameScene::SpawnScoreLabel() {
        ScoreLabel = Label::createWithTTF(toString<size_t>(Score), FONT, SCORE_FONT_SIZE);
        ScoreLabel->setColor(GAME_TEXT_COLOR);
        ScoreLabel->setPosition({WindowSize.width * SCORE_HORIZONTAL_OFFSET, WindowSize.height * SCORE_VERTICAL_OFFSET});

        addChild(ScoreLabel);
    }

    void GameScene::SpawnMenu() {
        auto menuItemLabel = Label::createWithTTF("Menu", FONT, GAME_MENU_FONT_SIZE);
        menuItemLabel->setColor(GAME_TEXT_COLOR);

        auto menuItem = MenuItemLabel::create(
            menuItemLabel,
            [&](Ref *sender){
                auto scene = MenuScene::createScene();
                Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
            }
        );
        menuItem->setPosition({WindowSize.width * MENU_HORIZONTAL_OFFSET, WindowSize.height * MENU_VERTICAL_OFFSET});

        auto menu = Menu::create(menuItem, nullptr);
        menu->setPosition(Point::ZERO);

        addChild(menu);
    }

    void GameScene::SpawnBird() {
        Bird.reset(new TBird(WindowSize));

        auto node = Bird->Spawn({WindowSize.width * BIRD_HORIZONTAL_OFFSET, WindowSize.height * BIRD_VERTICAL_OFFSET});
        addChild(node);
    }

    void GameScene::SpawnEdge() {
        Edge.reset(new TEdge(WindowSize));

        auto node = Edge->Spawn({WindowSize.width / 2, WindowSize.height / 2});
        addChild(node);
    }

    void GameScene::SpawnPipes(float dt) {
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

    bool GameScene::OnContactBegin(PhysicsContact &contact) {
        auto firstNodeBitmask = contact.getShapeA()->getBody()->getCategoryBitmask();
        auto secondNodeBitmask = contact.getShapeB()->getBody()->getCategoryBitmask();

        if (
            firstNodeBitmask != static_cast<int>(EPhysicsCategory::Obstacle) &&
            secondNodeBitmask != static_cast<int>(EPhysicsCategory::Obstacle)
        ) {
            ++Score;
            ScoreLabel->setString(toString<size_t>(Score));
        } else {
            auto scene = GameScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
        }

        return true;
    }

    bool GameScene::OnTouchBegin(Touch *touch, Event *event) {
        BirdStartFlying();
        scheduleOnce(schedule_selector(GameScene::BirdStopFlying), BIRD_FLY_DURATION);

        return true;
    }

    void GameScene::BirdStartFlying() {
        Bird->StartFlying();
    }

    void GameScene::BirdStopFlying(float dt) {
        Bird->StopFlying();
    }

    void GameScene::update(float dt) {
        Bird->Fly();
    }
}
