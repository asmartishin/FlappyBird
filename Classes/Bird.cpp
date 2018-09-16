#include "Bird.h"

using namespace cocos2d;

namespace NFlappyBird {
    TBird::TBird(Size windowSize)
        : TPhysics(windowSize)
    {
    }

    TNode TBird::InitNode(const Vec2& position) {
        Size size(WindowSize.height * BIRD_SIZE, WindowSize.height * BIRD_SIZE);
        Radius = size.width / 2;

        NodePtr = DrawNode::create();

        TNode node(NodePtr, size);

        dynamic_cast<DrawNode*>(node.Get())->drawSolidCircle(
            {0, 0}, Radius, 0.0f, 100, BIRD_COLOR
        );

        node->setPosition({Radius + position.x, position.y - Radius});

        return node;
    }

    void TBird::ApplyPhysics(TNode &node) {
        auto physicsBody = PhysicsBody::createCircle(Radius);

        physicsBody->setDynamic(false);
        physicsBody->setCategoryBitmask(static_cast<int>(EPhysicsCategory::Bird));
        physicsBody->setContactTestBitmask(static_cast<int>(EPhysicsCategory::All));

        node->setPhysicsBody(physicsBody);
    }

    TBirdCustom::TBirdCustom(Size windowSize)
        : TBird(windowSize)
    {
    }

    void TBirdCustom::Fly() {
        if (Flying) {
            NodePtr->setPositionY(NodePtr->getPositionY() + (BIRD_FALL_SPEED - BIRD_GRAVITY_FORCE) * WindowSize.height);
        } else {
            NodePtr->setPositionY(NodePtr->getPositionY() - (BIRD_FALL_SPEED + BIRD_GRAVITY_FORCE) * WindowSize.height);
        }
    }

    void TBirdCustom::StartFlying() {
        Flying = true;
    }

    void TBirdCustom::StopFlying() {
        Flying = false;
    }

    TBirdBox::TBirdBox(Size windowSize, b2World* world)
        : TBird(windowSize)
        , World(world)
        , Fixture(new b2FixtureDef())
        , Shape(new b2CircleShape())
        , Def(new b2BodyDef())
    {
    }

    void TBirdBox::ApplyPhysics(TNode &node) {
        TBird::ApplyPhysics(node);

        Shape->m_radius = Radius / BOX_SCALE_RATIO;

        Fixture->density = 0;
        Fixture->friction = 0;
        Fixture->restitution = 0;
        Fixture->shape = Shape.get();

        Def->type = b2_dynamicBody;
        Def->userData = NodePtr;

        Def->position.Set(NodePtr->getPositionX() / BOX_SCALE_RATIO, NodePtr->getPositionY() / BOX_SCALE_RATIO);

        Body = World->CreateBody(Def.get());
        Body->CreateFixture(Fixture.get());
        Body->SetGravityScale(BOX_BIRD_GRAVITY_SCALE);
    }

    void TBirdBox::Fly() {
        b2Vec2 vel = Body->GetLinearVelocity();
        vel.y = BOX_BIRD_VERTICAL_VELOCITY;
        Body->SetLinearVelocity(vel);
    }
}
