#pragma once

#include "cocos2d.h"

#include "Const.h"
#include "CustomPhysicsGameScene.h"

namespace NFlappyBird {
    class TMainMenuScene : public cocos2d::Layer {
    public:
        static cocos2d::Scene* createScene();

        bool init() override final;

        CREATE_FUNC(TMainMenuScene);
    };
}
