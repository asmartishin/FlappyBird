#pragma once

#include <memory>

#include "cocos2d.h"

#include "AbstractGameScene.h"
#include "Const.h"
#include "Bird.h"

namespace NFlappyBird {
    class TCustomPhysicsGameScene final: public TAbstractGameScene {
    public:
        static cocos2d::Scene *createScene();
        bool init() override final;

        CREATE_FUNC(TCustomPhysicsGameScene);
    private:
        std::unique_ptr<TBirdCustom> Bird;

        void SpawnBird() override final;
        bool OnTouchBegin(cocos2d::Touch *touch, cocos2d::Event *event) override final;
        void BirdStartFlying();
        void BirdStopFlying(float dt);
        void update(float dt) override final;
        void Restart() override final;
    };
};