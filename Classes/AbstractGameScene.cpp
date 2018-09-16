#include "AbstractGameScene.h"
// TODO: Better composition
#include "MainMenuScene.h"

using namespace cocos2d;

namespace NFlappyBird {
    bool TAbstractGameScene::init() {
        if (!Layer::init()) {
            return false;
        }

        auto director = Director::getInstance();

        WindowSize = director->getWinSize();
        Origin = director->getVisibleOrigin();

        auto background = DrawNode::create();
        background->drawSolidRect(Origin, WindowSize, GAME_BACKGROUND_COLOR);
        addChild(background);

        Pipes = {
            std::unique_ptr<TPipe>(new TTopPipe(WindowSize)),
            std::unique_ptr<TPipe>(new TBottomPipe(WindowSize)),
            std::unique_ptr<TPipe>(new TTarget(WindowSize))
        };

        SpawnEdge();
        SpawnScoreLabel();
        SpawnMenu();

        srand(static_cast<unsigned int>(time(nullptr)));
        schedule(schedule_selector(TAbstractGameScene::SpawnPipes), PIPE_SPAWN_FREQUENCY);

        auto contactListener = EventListenerPhysicsContact::create();
        contactListener->onContactBegin = CC_CALLBACK_1(TAbstractGameScene::OnContactBegin, this);
        getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

        scheduleUpdate();

        return true;
    }

    void TAbstractGameScene::SpawnScoreLabel() {
        ScoreLabel = Label::createWithTTF(toString<size_t>(Score), FONT, SCORE_FONT_SIZE);
        ScoreLabel->setColor(GAME_TEXT_COLOR);
        ScoreLabel->setPosition({WindowSize.width * SCORE_HORIZONTAL_OFFSET, WindowSize.height * SCORE_VERTICAL_OFFSET});

        addChild(ScoreLabel);
    }

    void TAbstractGameScene::SpawnMenu() {
        auto menuItemLabel = Label::createWithTTF("Menu", FONT, GAME_MENU_FONT_SIZE);
        menuItemLabel->setColor(GAME_TEXT_COLOR);

        auto menuItem = MenuItemLabel::create(
            menuItemLabel,
            [&](Ref *sender){
                auto scene = TMainMenuScene::createScene();
                Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
            }
        );
        menuItem->setPosition({WindowSize.width * MENU_HORIZONTAL_OFFSET, WindowSize.height * MENU_VERTICAL_OFFSET});

        auto menu = Menu::create(menuItem, nullptr);
        menu->setPosition(Point::ZERO);

        addChild(menu);
    }

    void TAbstractGameScene::SpawnEdge() {
        Edge.reset(new TEdge(WindowSize));

        auto node = Edge->Spawn({WindowSize.width / 2, WindowSize.height / 2});
        addChild(node);
    }

    void TAbstractGameScene::SpawnPipes(float dt) {
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

    bool TAbstractGameScene::OnContactBegin(PhysicsContact &contact) {
        auto firstNodeBitmask = contact.getShapeA()->getBody()->getCategoryBitmask();
        auto secondNodeBitmask = contact.getShapeB()->getBody()->getCategoryBitmask();

        if (firstNodeBitmask != static_cast<int>(EPhysicsCategory::Obstacle) &&
            secondNodeBitmask != static_cast<int>(EPhysicsCategory::Obstacle))
        {
            ++Score;
            ScoreLabel->setString(toString<size_t>(Score));
        } else {
            Restart();
        }

        return true;
    }
}
