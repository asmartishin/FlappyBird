#pragma once

#include <memory>

#include "cocos2d.h"

#include "AbstractGameScene.h"
#include "Const.h"
#include "Pipe.h"
#include "Bird.h"
#include "Edge.h"
#include "Util.h"

namespace NFlappyBird {
    class TCustomPhysicsGameScene final: public TAbstractGameScene {
    public:
        static cocos2d::Scene *createScene();
        bool init() override final;

        CREATE_FUNC(TCustomPhysicsGameScene);
    private:
        std::unique_ptr<TBird> Bird;
        std::unique_ptr<TEdge> Edge;

        std::array<std::unique_ptr<TPipe>, 3> Pipes;

        void SpawnBird() override final;
        void SpawnEdge() override final;
        void SpawnPipes(float dt) override final;
        bool OnContactBegin(cocos2d::PhysicsContact &contact);
        bool OnTouchBegin(cocos2d::Touch *touch, cocos2d::Event *event);
        void BirdStartFlying();
        void BirdStopFlying(float dt);
        void update(float dt) override final;
    };
};