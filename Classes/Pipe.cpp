#include "Pipe.h"

using namespace cocos2d;

namespace NFlappyBird {
    TPipe::TPipe(Size windowSize)
        : TPhysics(windowSize)
        , GapWidth(windowSize.width * PIPE_WIDTH)
        , GapHeight(windowSize.height * GAP_HEIGHT)
    {
    }

    void TPipe::ApplyPhysics(TNode &node) {
        auto physicsBody = PhysicsBody::createBox(node.Size());

        physicsBody->setDynamic(false);
        physicsBody->setCategoryBitmask(static_cast<int>(EPhysicsCategory::Obstacle));
        physicsBody->setCollisionBitmask(static_cast<int>(EPhysicsCategory::None));
        physicsBody->setContactTestBitmask(static_cast<int>(EPhysicsCategory::Bird));

        node->setPhysicsBody(physicsBody);
    }

    TTopPipe::TTopPipe(Size windowSize)
        : TPipe(windowSize)
    {
    }

    TNode TTopPipe::InitNode(const cocos2d::Vec2& position) {
        Size size(GapWidth, WindowSize.height - GapHeight - position.y);
        TNode node(DrawNode::create(), size);

        dynamic_cast<DrawNode*>(node.Get())->drawSolidRect(
            {-size.width / 2, -size.height / 2},
            {size.width / 2, size.height / 2},
            PIPE_COLOR
        );

        node->setPosition({WindowSize.width + size.width / 2, position.y + GapHeight + size.height / 2});

        return node;
    }

    TBottomPipe::TBottomPipe(Size windowSize)
        : TPipe(windowSize)
    {
    }

    TNode TBottomPipe::InitNode(const cocos2d::Vec2& position) {
        Size size(GapWidth, position.y);
        TNode node(DrawNode::create(), size);

        dynamic_cast<DrawNode*>(node.Get())->drawSolidRect(
            {-size.width / 2, -size.height / 2},
            {size.width / 2, size.height / 2},
            PIPE_COLOR
        );

        node->setPosition({WindowSize.width + size.width / 2, size.height / 2});

        return node;
    }

    TTarget::TTarget(Size windowSize)
        : TPipe(windowSize)
    {
    };

    TNode TTarget::InitNode(const cocos2d::Vec2& position) {
        Size size(GapWidth, GapHeight);
        TNode node(Node::create(), size);

        node->setPosition({WindowSize.width + size.width / 2, position.y + size.height / 2});

        return node;
    }

    void TTarget::ApplyPhysics(TNode& node) {
        auto physicsBody = PhysicsBody::createBox(node.Size());

        physicsBody->setDynamic(false);
        physicsBody->setCategoryBitmask(static_cast<int>(EPhysicsCategory::Target));
        physicsBody->setContactTestBitmask(static_cast<int>(EPhysicsCategory::Bird));

        node->setPhysicsBody(physicsBody);
    }
}