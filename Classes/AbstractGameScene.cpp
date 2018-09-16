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

        SpawnScoreLabel();
        SpawnMenu();

        srand(static_cast<unsigned int>(time(nullptr)));

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
}
