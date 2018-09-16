#pragma once

#include <array>

#include "cocos2d.h"

#include "Const.h"
#include "Util.h"
#include "Edge.h"
#include "Pipe.h"

namespace NFlappyBird {
    class TAbstractGameScene: public cocos2d::Layer {
    public:
        virtual ~TAbstractGameScene() = default;
        virtual bool init() override;

    protected:
        cocos2d::Size WindowSize;
        cocos2d::Vec2 Origin;
        cocos2d::Label* ScoreLabel;

        std::unique_ptr<TEdge> Edge;
        std::array<std::unique_ptr<TPipe>, 3> Pipes;

        std::size_t Score;
    private:
        void SpawnScoreLabel();
        void SpawnMenu();
        void SpawnEdge();
        virtual void SpawnPipes(float dt);

        virtual bool OnContactBegin(cocos2d::PhysicsContact &contact);

        virtual void SpawnBird() = 0;
        virtual void Restart() = 0;
        virtual bool OnTouchBegin(cocos2d::Touch *touch, cocos2d::Event *event) = 0;
    };
}