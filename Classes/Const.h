#pragma once

#include <string>

#include "cocos2d.h"

namespace NFlappyBird {
    constexpr float BIRD_SIZE = 0.108;
    constexpr float BIRD_HORIZONTAL_OFFSET = 0.1;
    constexpr float BIRD_VERTICAL_OFFSET = 0.9; // from bottom
    constexpr float BIRD_FLY_DURATION = 0.31;
    constexpr float BIRD_FALL_SPEED = 0.01;
    constexpr float BIRD_GRAVITY_FORCE = BIRD_FALL_SPEED / 4.6f;
    constexpr float PIPE_SPAWN_FREQUENCY = 1.4; // less is more often
    constexpr float PIPE_MOVE_SPEED = 4; // less is faster
    constexpr float PIPE_WIDTH = 0.085;
    constexpr float GAP_HEIGHT = 0.32;
    constexpr float TRANSITION_TIME = 0.5;
    constexpr float SCORE_FONT_SIZE = 26;
    constexpr float MAIN_MENU_FONT_SIZE = 28;
    constexpr float GAME_MENU_FONT_SIZE = 22;
    constexpr float SCORE_HORIZONTAL_OFFSET = 0.08;
    constexpr float SCORE_VERTICAL_OFFSET = 0.14;
    constexpr float MENU_VERTICAL_OFFSET = 1 - SCORE_VERTICAL_OFFSET;
    constexpr float MENU_HORIZONTAL_OFFSET = SCORE_HORIZONTAL_OFFSET;
    constexpr float BOX_SCALE_RATIO = 16;
    constexpr float BOX_GRAVITY = -9.8f;
    constexpr float BOX_BIRD_GRAVITY_SCALE = 3;
    constexpr float BOX_BIRD_VERTICAL_VELOCITY = 15;
    constexpr int POSITION_ITERATIONS = 10;
    constexpr int VELOCITY_ITERATIONS = 10;
    static const cocos2d::Color3B GAME_TEXT_COLOR(0, 0, 0);
    static const cocos2d::Color3B MENU_TEXT_COLOR(255, 255, 255);
    static const cocos2d::Color4F GAME_BACKGROUND_COLOR(1, 1, 1, 1);
    static const cocos2d::Color4F MENU_BACKGROUND_COLOR(0, 0, 0, 1);
    static const cocos2d::Color4F PIPE_COLOR(0, 0, 0, 1);
    static const cocos2d::Color4F BIRD_COLOR(0, 0, 0, 1);
    static const std::string FONT = "fonts/Roboto.ttf";
}
