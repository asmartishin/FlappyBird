#pragma once

#include "cocos2d.h"

#include "Const.h"
#include "GameScene.h"

namespace NFlappyBird {
    class MenuScene : public cocos2d::Layer {
    public:
        static cocos2d::Scene* createScene();

        bool init() override final;

        CREATE_FUNC(MenuScene);
    private:
        void ToGameScene(cocos2d::Ref* sender);
    };
}