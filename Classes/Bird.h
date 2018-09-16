#pragma once

#include "cocos2d.h"
#include <Box2D/Box2D.h>

#include "Physics.h"
#include "Const.h"

namespace NFlappyBird {
    class TBird: public TPhysics {
    public:
        TBird(cocos2d::Size windowSize);
        virtual ~TBird() = default;
        virtual void Fly() = 0;
    protected:
        cocos2d::DrawNode* NodePtr;
        float Radius;
        virtual void ApplyPhysics(TNode &node) override;
    private:
        TNode InitNode(const cocos2d::Vec2& position) override final;
    };

    class TBirdCustom final: public TBird {
    public:
        TBirdCustom(cocos2d::Size windowSize);

        void Fly() override final;
        void StartFlying();
        void StopFlying();
    private:
        bool Flying = false;
    };

    class TBirdBox final: public TBird {
    public:
        TBirdBox(cocos2d::Size windowSize, b2World* world);
        void Fly() override final;

        b2Body* GetBody() const noexcept {
            return Body;
        }
    private:
        void ApplyPhysics(TNode &node) override final;

        b2World* World;
        std::unique_ptr<b2FixtureDef> Fixture;
        std::unique_ptr<b2CircleShape> Shape;
        std::unique_ptr<b2BodyDef> Def;
        b2Body* Body;
    };
};