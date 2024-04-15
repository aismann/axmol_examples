/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2021 Bytedance Inc.

 https://axmolengine.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "axmol.h"


class MainScene : public ax::Scene
{
    enum class GameState
    {
        init = 0,
        update,
        pause,
        end,
        menu1,
        menu2,
    };

    
public:
    bool init() override;
    void update(float delta) override;

    // touch
    void onTouchesBegan(const std::vector<ax::Touch*>& touches, ax::Event* event);
    void onTouchesMoved(const std::vector<ax::Touch*>& touches, ax::Event* event);
    void onTouchesEnded(const std::vector<ax::Touch*>& touches, ax::Event* event);

    // mouse
    void onMouseDown(ax::Event* event);
    void onMouseUp(ax::Event* event);
    void onMouseMove(ax::Event* event);
    void onMouseScroll(ax::Event* event);

    // Keyboard
    void onKeyPressed(ax::EventKeyboard::KeyCode code, ax::Event* event);
    void onKeyReleased(ax::EventKeyboard::KeyCode code, ax::Event* event);

    // a selector callback
    void menuCloseCallback(Ref* sender);

private:
    GameState _gameState = GameState::init;
    ax::DrawNode* draw;
    ax::DrawNode* drawUpdate;

#define _XXX 10
#define _YYY 10 
    int xx = _XXX;
    int yy = _YYY;
    int xStart = 50;
    int yStart = 50;
    int xWidth = 60;
    int yWidth = 60;

    int grid[_XXX][_YYY];
    ax::Label* gridValue[_XXX][_YYY];
    ax::Sprite* gridSprite[_XXX][_YYY];
    int maxFox = 10;
    int foundFox = 0;

  //  std::string fox = "istockphoto-516954884-612x612.jpg";
    std::string_view fox = "108861585.png";

    ax::Color3B countColor[_XXX+1] = {    ax::Color3B::WHITE,     // (255, 255, 255)
                                        ax::Color3B::BLUE,      // (0, 0, 255)
                                        ax::Color3B::YELLOW,    // (255, 255, 0)
                                        ax::Color3B::GREEN,     // (0, 255, 0)
                                        ax::Color3B::RED,       // (255, 0, 0)
                                        ax::Color3B::MAGENTA,   // (255, 0, 255)
                                        ax::Color3B(255,200,50),
                                        ax::Color3B::ORANGE,    // (255, 127, 0)
                                        ax::Color3B::GRAY,      // (166, 166, 166);
                                        ax::Color3B(255,0,50),  
                                        ax::Color3B(0,200,50) };


};

#endif  // __MAIN_SCENE_H__
