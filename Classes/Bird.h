#pragma once

#include "cocos2d.h"

#include "Physics.h"
#include "Const.h"

namespace NFlappyBird {
    class TBird: public TPhysics {
    public:
        TBird(cocos2d::Size windowSize);

        void Fly();
        void StartFlying();
        void StopFlying();
    private:
        TNode InitNode(const cocos2d::Vec2& position) override final;
        void applyPhysics(TNode &node) override final;

        cocos2d::DrawNode* NodePtr;
        bool Flying = false;
    };
};