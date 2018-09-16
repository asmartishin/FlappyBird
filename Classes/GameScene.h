#pragma once

#include <memory>
#include <array>
#include <string>

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#include "Const.h"
#include "Pipe.h"
#include "Bird.h"
#include "Edge.h"
#include "MenuScene.h"
#include "Util.h"

namespace NFlappyBird {
    class GameScene : public cocos2d::Layer {
    public:
        static cocos2d::Scene *createScene();
        bool init() override final;

        CREATE_FUNC(GameScene);
    private:
        cocos2d::Size WindowSize;
        cocos2d::Vec2 Origin;

        std::size_t Score;

        cocos2d::Label* ScoreLabel;
        std::unique_ptr<TBird> Bird;
        std::unique_ptr<TEdge> Edge;

        std::array<std::unique_ptr<TPipe>, 3> Pipes;

        void SpawnScoreLabel();
        void SpawnMenu();
        void SpawnBird();
        void SpawnEdge();
        void SpawnPipes(float dt);
        bool OnContactBegin(cocos2d::PhysicsContact &contact);
        bool OnTouchBegin(cocos2d::Touch *touch, cocos2d::Event *event);
        void BirdStartFlying();
        void BirdStopFlying(float dt);
        void update(float dt) override final;
    };
}