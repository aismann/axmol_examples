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

#include "MainScene.h"

USING_NS_AX;

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf(
        "Depending on how you compiled you might have to add 'Content/' in front of filenames in "
        "MainScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    auto safeArea = _director->getSafeAreaRect();
    auto safeOrigin = safeArea.origin;

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    //// add a "close" icon to exit the progress. it's an autorelease object
    //auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
    //    AX_CALLBACK_1(MainScene::menuCloseCallback, this));

    //if (closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0)
    //{
    //    problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    //}
    //else
    //{
    //    float x = safeOrigin.x + safeArea.size.width - closeItem->getContentSize().width / 2;
    //    float y = safeOrigin.y + closeItem->getContentSize().height / 2;
    //    closeItem->setPosition(Vec2(x, y));
    //}

    //// create menu, it's an autorelease object
    //auto menu = Menu::create(closeItem, NULL);
    //menu->setPosition(Vec2::ZERO);
    //this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // Some templates (uncomment what you  need)
    auto touchListener = EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesBegan = AX_CALLBACK_2(MainScene::onTouchesBegan, this);
    touchListener->onTouchesMoved = AX_CALLBACK_2(MainScene::onTouchesMoved, this);
    touchListener->onTouchesEnded = AX_CALLBACK_2(MainScene::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    //auto mouseListener           = EventListenerMouse::create();
    //mouseListener->onMouseMove   = AX_CALLBACK_1(MainScene::onMouseMove, this);
    //mouseListener->onMouseUp     = AX_CALLBACK_1(MainScene::onMouseUp, this);
    //mouseListener->onMouseDown   = AX_CALLBACK_1(MainScene::onMouseDown, this);
    //mouseListener->onMouseScroll = AX_CALLBACK_1(MainScene::onMouseScroll, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    //auto keyboardListener           = EventListenerKeyboard::create();
    //keyboardListener->onKeyPressed  = AX_CALLBACK_2(MainScene::onKeyPressed, this);
    //keyboardListener->onKeyReleased = AX_CALLBACK_2(MainScene::onKeyReleased, this);
    //_eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, 11);



    // add a label shows "Hello World"
    // create and initialize a label

    //auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    //if (label == nullptr)
    //{
    //    problemLoading("'fonts/Marker Felt.ttf'");
    //}
    //else
    //{
    //    // position the label on the center of the screen
    //    label->setPosition(
    //        Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));

    //    // add the label as a child to this layer
    //    this->addChild(label, 1);
    //}
    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png"sv);
    //if (sprite == nullptr)
    //{
    //    problemLoading("'HelloWorld.png'");
    //}
    //else
    //{
    //    // position the sprite on the center of the screen
    //    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    //    // add the sprite as a child to this layer
    //    this->addChild(sprite, 0);
    //    auto drawNode = DrawNode::create();
    //    drawNode->setPosition(Vec2(0, 0));
    //    addChild(drawNode);

    //    drawNode->drawRect(safeArea.origin + Vec2(1, 1), safeArea.origin + safeArea.size, Color4F::BLUE);
    //}

    // scheduleUpdate() is required to ensure update(float) is called on every loop
    scheduleUpdate();

    return true;
}


void MainScene::onTouchesBegan(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
        AXLOG("onTouchesBegan detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
        int  xx =  (t->getLocation().x - xStart ) /  xWidth;
        int  yy =  (t->getLocation().y - yStart ) /  yWidth;
        if (grid[xx][yy] >= 100)
        {
            gridSprite[xx][yy]->setVisible(true);
            foundFox++;
            if (foundFox >= maxFox)
            {
                //  I am a WINNNER!!!!
            }
        }
        else
        {
            gridValue[xx][yy]->setVisible(true);
        }
    }

  //  gridSprite[x][y]->setPosition(Vec2(xStart + x * xWidth + xWidth / 2, yStart + y * yWidth + yWidth / 2));



}

void MainScene::onTouchesMoved(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
        AXLOG("onTouchesMoved detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
    }
}

void MainScene::onTouchesEnded(const std::vector<ax::Touch*>& touches, ax::Event* event)
{
    for (auto&& t : touches)
    {
        AXLOG("onTouchesEnded detected, X:%f  Y:%f", t->getLocation().x, t->getLocation().y);
    }
}

void MainScene::onMouseDown(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    AXLOG("onMouseDown detected, Key: %d", static_cast<int>(e->getMouseButton()));
}

void MainScene::onMouseUp(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    AXLOG("onMouseUp detected, Key: %d", static_cast<int>(e->getMouseButton()));
}

void MainScene::onMouseMove(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    AXLOG("onMouseMove detected, X:%f  Y:%f", e->getCursorX(), e->getCursorY());
}

void MainScene::onMouseScroll(Event* event)
{
    EventMouse* e = static_cast<EventMouse*>(event);
    AXLOG("onMouseScroll detected, X:%f  Y:%f", e->getScrollX(), e->getScrollY());
}

void MainScene::onKeyPressed(EventKeyboard::KeyCode code, Event* event)
{
    AXLOG("onKeyPressed, keycode: %d", static_cast<int>(code));
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode code, Event* event)
{
    AXLOG("onKeyReleased, keycode: %d", static_cast<int>(code));
}

void MainScene::update(float delta)
{
    switch (_gameState)
    {
    case GameState::init:
    {
        draw = DrawNode::create();
        addChild(draw, 10);

        drawUpdate = DrawNode::create();
        addChild(drawUpdate, 10);


        // init the grid
        {
            for (int x = 0; x < xx; x++)
                for (int y = 0; y < yy; y++)
                {
                    grid[x][y] = 0;
                    gridSprite[x][y] = Sprite::create(fox);
                    addChild(gridSprite[x][y],10);
                }
        }

        // Set the fox, fill the grid
        srand((unsigned  int)time(0));
        for (int n = 0; n < maxFox; n++)
        {
            int xR = -1;
            int yR = -1;
            do
            {
                xR = rand() % xx;
                yR = rand() % yy;
                if (grid[xR][yR] < 100)
                {
                    grid[xR][yR] += 100;
                    break;
                }
            } while (true);

            for (int i = 0; i < xx; i++)  // - waagrecht
                grid[i][yR]++;
            for (int i = 0; i < yy; i++)  // | senkrecht
                grid[xR][i]++;

            int _x = xR;
            int _y = yR;

            do // /+
            {
                if (grid[_x][_y] < 100)
                {
                    grid[_x][_y]++;
                }
                _x++;
                _y++;
            } while (_x < xx && _y < yy);

            _x = xR;
            _y = yR;
            do // /-
            {
                if (grid[_x][_y] < 100)
                {
                    grid[_x][_y]++;
                }
                _x--;
                _y--;
            } while (_x >= 0 && _y >= 0);

            _x = xR;
            _y = yR;
            do // \+
            {
                if (grid[_x][_y] < 100)
                {
                    grid[_x][_y]++;
                }
                _x--;
                _y++;
            } while (_x >= 0 && _y < yy);
            _x = xR;
            _y = yR;

            do // \-
            {
                if (grid[_x][_y] < 100)
                {
                    grid[_x][_y]++;
                }
                _x++;
                _y--;
            } while (_x < xx && _y >= 0);
        }


        // init the grid
        {
            for (int x = 0; x < xx; x++)
            {
                for (int y = 0; y < yy; y++)
                {
                    gridValue[x][y] = Label::createWithTTF(std::to_string(grid[x][y]).c_str(), "fonts/Marker Felt.ttf", 24);
                    gridValue[x][y]->setVisible(false); 

                    if (gridValue[x][y])
                    {
                        gridValue[x][y]->setPosition(Vec2(xStart + x * xWidth + xWidth / 2, yStart + y * yWidth + yWidth / 2));
                        addChild(gridValue[x][y], 1);
                        gridSprite[x][y]->setVisible(false);
                        gridSprite[x][y]->setScale(0.29);
                        gridSprite[x][y]->setPosition(Vec2(xStart + x * xWidth + xWidth / 2, yStart + y * yWidth + yWidth / 2));
                        if (grid[x][y] >= 100)
                        {
                            gridValue[x][y]->setVisible(false);
                        }
                        else
                        {
                            gridValue[x][y]->setColor(countColor[grid[x][y]]);
                        }
 
                    }
                    else
                    {
                        AXLOG("ERROR");
                    }

             //       AXLOG("%s", std::to_string(grid[x][y]).c_str());
             ////       gridValue[x][y]->setString(std::to_string(grid[x][y]));
             //    //   gridValue[x][y]->setString(std::to_string(grid[x][y]).c_str());
                }
            }
        }

        draw->clear();
        for (int x = 0; x <= xx; x++)
        {
            draw->drawLine(Vec2(xStart + x * xWidth, yStart), Vec2(xStart + x * xWidth, yStart + (xWidth * yy)), Color4B::GREEN);
        }
        for (int y = 0; y <= yy; y++)
        {
            draw->drawLine(Vec2(xStart, yStart + y * yWidth), Vec2(xStart + (yWidth * xx), yStart + y * yWidth), Color4B::GREEN);
        }

        _gameState = GameState::update;
        break;
    }

    case GameState::update:
    {
        /////////////////////////////
        // Add your codes below...like....
        // 
        // UpdateJoyStick();
        // UpdatePlayer();
        // UpdatePhysics();
        // ...
        drawUpdate->clear();
        // draw the grid content
        {
            for (int x = 0; x < xx; x++)
                for (int y = 0; y < yy; y++)
                    if (grid[x][y] >= 100)
                    {
      //                  gridSprite[x][y]->setVisible(true);
                     //   drawUpdate->drawSolidCircle(Vec2(xStart + x * xWidth + xWidth / 2, yStart + y * yWidth + yWidth / 2), /*Vec2(xStart + x * xWidth, yStart+(xWidth*yy)),*/ 10, 90, 10, Color4B(Color4B::RED));
                    }
        }

        break;
    }

    case GameState::pause:
    {
        /////////////////////////////
        // Add your codes below...like....
        //
        // anyPauseStuff()

        break;
    }

    case GameState::menu1:
    {    /////////////////////////////
        // Add your codes below...like....
        // 
        // UpdateMenu1();
        break;
    }

    case GameState::menu2:
    {    /////////////////////////////
        // Add your codes below...like....
        // 
        // UpdateMenu2();
        break;
    }

    case GameState::end:
    {    /////////////////////////////
        // Add your codes below...like....
        // 
        // CleanUpMyCrap();
        menuCloseCallback(this);
        break;
    }

    } //switch
}

void MainScene::menuCloseCallback(Ref* sender)
{
    // Close the axmol game scene and quit the application
    _director->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use
     * _director->end() as given above,instead trigger a custom event created in RootViewController.mm
     * as below*/

     // EventCustom customEndEvent("game_scene_close_event");
     //_eventDispatcher->dispatchEvent(&customEndEvent);
}
