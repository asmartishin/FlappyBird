#include "MainMenuScene.h"

using namespace cocos2d;

namespace NFlappyBird {
    Scene* TMainMenuScene::createScene() {
        auto scene = Scene::create();

        auto layer = TMainMenuScene::create();

        scene->addChild(layer);

        return scene;
    }

    bool TMainMenuScene::init() {
        if (!Layer::init()) {
            return false;
        }

        auto director = Director::getInstance();

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
                auto scene = TCustomPhysicsGameScene::createScene();
                Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
            }
        );
        customPhysicsMenuItem->setPosition({windowSize.width / 2, windowSize.height / 3 * 2});

        auto boxPhysicsMenuItemLabel = Label::createWithTTF("Box2D physics", FONT, MAIN_MENU_FONT_SIZE);
        boxPhysicsMenuItemLabel->setColor(MENU_TEXT_COLOR);

        auto boxPhysicsMenuItem = MenuItemLabel::create(
            boxPhysicsMenuItemLabel,
            [&](Ref *sender){
                auto scene = TBoxPhysicsGameScene::createScene();
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
