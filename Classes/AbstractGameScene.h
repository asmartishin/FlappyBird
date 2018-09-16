#pragma once

#include "cocos2d.h"

#include "Const.h"
#include "Util.h"

namespace NFlappyBird {
    class TAbstractGameScene: public cocos2d::Layer {
    public:
        virtual ~TAbstractGameScene() = default;
        virtual bool init() override;

    protected:
        cocos2d::Size WindowSize;
        cocos2d::Vec2 Origin;
        cocos2d::Label* ScoreLabel;

        std::size_t Score;
    private:
        void SpawnScoreLabel();
        void SpawnMenu();
        virtual void SpawnBird() = 0;
        virtual void SpawnEdge() = 0;
        virtual void SpawnPipes(float dt) = 0;
        virtual bool OnContactBegin(cocos2d::PhysicsContact &contact) = 0;
        virtual bool OnTouchBegin(cocos2d::Touch *touch, cocos2d::Event *event) = 0;
    };
}