#include "MenuScene.h"

using namespace cocos2d;

namespace NFlappyBird {
    Scene *MenuScene::createScene() {
        auto scene = Scene::create();

        auto layer = MenuScene::create();

        scene->addChild(layer);

        return scene;
    }

    bool MenuScene::init() {
        if (!Layer::init()) {
            return false;
        }

        auto director = Director::getInstance();

        director->setDisplayStats(false);
        auto windowSize = director->getWinSize();
        auto origin = director->getVisibleOrigin();

        auto background = DrawNode::create();
        background->drawSolidRect(origin, windowSize, MENU_BACKGROUND_COLOR);
        addChild(background);

        Vector<MenuItem*> menuItems;

        auto customPhysicsMenuItemLabel = Label::createWithTTF("Custom physics", FONT, MAIN_MENU_FONT_SIZE);
        customPhysicsMenuItemLabel->setColor(MENU_TEXT_COLOR);

        auto customPhysicsMenuItem = MenuItemLabel::create(
            customPhysicsMenuItemLabel,
            [&](Ref *sender){
                auto scene = GameScene::createScene();
                Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
            }
        );
        customPhysicsMenuItem->setPosition({windowSize.width / 2, windowSize.height / 3 * 2});

        auto boxPhysicsMenuItemLabel = Label::createWithTTF("Box2D physics", FONT, MAIN_MENU_FONT_SIZE);
        boxPhysicsMenuItemLabel->setColor(MENU_TEXT_COLOR);

        auto boxPhysicsMenuItem = MenuItemLabel::create(
            boxPhysicsMenuItemLabel,
            [&](Ref *sender){
                auto scene = GameScene::createScene();
                Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
            }
        );
        boxPhysicsMenuItem->setPosition({windowSize.width / 2, windowSize.height / 3});

        menuItems.pushBack(customPhysicsMenuItem);
        menuItems.pushBack(boxPhysicsMenuItem);

        auto menu = Menu::createWithArray(menuItems);
        menu->setPosition(Point::ZERO);

        addChild(menu);

        return true;
    }
}