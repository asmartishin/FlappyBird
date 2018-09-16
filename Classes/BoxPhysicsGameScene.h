#pragma once

#include <memory>

#include "cocos2d.h"
#include <Box2D/Box2D.h>

#include "AbstractGameScene.h"
#include "Bird.h"

USING_NS_CC;

namespace NFlappyBird {
    class TBoxPhysicsGameScene final: public TAbstractGameScene, public b2ContactListener {
    public:
        static Scene *createScene();

        virtual bool init();

        CREATE_FUNC(TBoxPhysicsGameScene);

    private:
        std::unique_ptr<b2World> World;
        std::unique_ptr<TBirdBox> Bird;

        bool OnTouchBegin(cocos2d::Touch *touch, cocos2d::Event *event) override final;

        void SpawnBird() override final;
        void update(float dt);

        void Restart() override final;
    };
}