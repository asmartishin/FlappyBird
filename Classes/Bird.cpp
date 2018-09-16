#include "Bird.h"

using namespace cocos2d;

namespace NFlappyBird {
    TBird::TBird(Size windowSize)
        : TPhysics(windowSize)
    {
    }

    TNode TBird::InitNode(const Vec2& position) {
        Size size(WindowSize.height * BIRD_SIZE, WindowSize.height * BIRD_SIZE);
        NodePtr = DrawNode::create();

        TNode node(NodePtr, size);

        dynamic_cast<DrawNode*>(node.Get())->drawSolidCircle(
            {0, 0}, size.width, 0.0f, 100, BIRD_COLOR
        );

        node->setPosition({size.width + position.x, position.y - size.width});

        return node;
    }

    void TBird::applyPhysics(TNode &node) {
        auto physicsBody = PhysicsBody::createCircle(node.Size().height);

        physicsBody->setDynamic(false);
        physicsBody->setCategoryBitmask(static_cast<int>(EPhysicsCategory::Bird));
        physicsBody->setContactTestBitmask(static_cast<int>(EPhysicsCategory::All));

        node->setPhysicsBody(physicsBody);
    }

    void TBird::StartFlying() {
        Flying = true;
    }

    void TBird::StopFlying() {
        Flying = false;
    }

    void TBird::Fly() {
        if (Flying) {
            NodePtr->setPositionY(NodePtr->getPositionY() + (BIRD_FALL_SPEED - BIRD_GRAVITY_FORCE) * WindowSize.height);
        } else {
            NodePtr->setPositionY(NodePtr->getPositionY() - (BIRD_FALL_SPEED + BIRD_GRAVITY_FORCE) * WindowSize.height);
        }
    }
}
