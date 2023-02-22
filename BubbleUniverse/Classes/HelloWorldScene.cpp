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

#include "HelloWorldScene.h"
#include <math.h>

USING_NS_AX;

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf(
        "Depending on how you compiled you might have to add 'Resources/' in front of filenames in "
        "HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();
    auto safeArea = _director->getSafeAreaRect();
    auto safeOrigin = safeArea.origin;

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
        AX_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr || closeItem->getContentSize().width <= 0 || closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = safeOrigin.x + safeArea.size.width - closeItem->getContentSize().width / 2;
        float y = safeOrigin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    //auto label = Label::createWithTTF("Bubble Universe", "fonts/Marker Felt.ttf", 24);
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
    drawNode = DrawNode::create();
    addChild(drawNode);
    //  _director->setAnimationInterval(1.0f / 1);
    scheduleUpdate();

    return true;
}

void HelloWorld::update(float delta)
{
    int nMode = 0;
    float u = 0;
    float v = 0;
    float x = 0;
    static float t = 0;
    float hh = 300; //visibleSize.y / 2;
    float hw = 300; //visibleSize.x / 2;
    const auto maximumStep = 1 / 3.f;
    auto progress = 0.0f;

    switch (_gameState)
    {
    case ExampleGameState::init:
        _gameState = ExampleGameState::update;
        break;

    case ExampleGameState::update:
        /////////////////////////////
        // Add your codes below...like....
        //
        // UpdateJoyStick();
        // UpdatePlayer();
        // UpdatePhysics();
        // ...

        drawNode->clear();
        while (progress < delta)
        {
            const auto step = std::min((delta - progress), maximumStep);
            progress += step;
            float r = AX_DOUBLE_PI / 255;


            int n = 200;

            //   if (nMode)
            {
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        u = sin(i + v) + sin(r * i + x);
                        v = cos(i + v) + cos(r * i + x);
                        x = u + t;

                        drawNode->drawPoint(Vec2(hw + u * hw * 0.4, hh + v * hh * 0.4), 1, Color4B(i, j, 99, 255));
                    }
                }
            }
            t += 0.001;
        }

        break;

    case ExampleGameState::pause:
        /////////////////////////////
        // Add your codes below...like....
        //
        // anyPauseStuff()
        break;

    case ExampleGameState::menu1:
        /////////////////////////////
        // Add your codes below...like....
        //
        // UpdateMenu1();
        break;

    case ExampleGameState::menu2:
        /////////////////////////////
        // Add your codes below...like....
        //
        // UpdateMenu2();
        break;

    case ExampleGameState::end:
        /////////////////////////////
        // Add your codes below...like....
        //
        // CleanUpMyCrap();
        menuCloseCallback(this);
        break;
    }
}

void HelloWorld::menuCloseCallback(Ref* sender)
{
    // Close the axmol game scene and quit the application
    _director->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use
     * _director->end() as given above,instead trigger a custom event created in RootViewController.mm
     * as below*/

     // EventCustom customEndEvent("game_scene_close_event");
     //_eventDispatcher->dispatchEvent(&customEndEvent);
}

//
//Enumeration
//#MainWindow
//#BubbleSprite
//        EndEnumeration
//
//            Macro ScaleFactor
//            DesktopResolutionX() EndMacro
//
//    Macro ScaleFactorM(value)(value) *
//    ScaleFactor EndMacro
//
//    InitSprite()
//
//        xmax = 600
//    : ymax   = 600
//
//      If OpenWindow(#MainWindow, 0, 0, xmax, ymax, "Bubble Universe", #PB_Window_SystemMenu | #PB_Window_ScreenCentered)
//          xmaxScaled = ScaleFactorM(xmax)
//    : ymaxScaled     = ScaleFactorM(ymax)
//
//                       If OpenWindowedScreen(WindowID(#MainWindow), 0, 0, xmaxScaled, ymaxScaled) SetFrameRate(60)
//                           CreateSprite(#BubbleSprite, xmaxScaled, ymaxScaled) TAU.f = #PI* 2 r.f =
//          TAU / 235 n = 200 t.f = 0 u.f = 0 v.f = 0 x.f = 0 hw = xmaxScaled / 2 hh =
//                                                                     ymaxScaled / 2
//
//                                                                     Repeat Repeat Event = WindowEvent()
//
//                                                                         If Event = #PB_Event_CloseWindow : Break 2
//    : EndIf
//
//      Until Not Event FlipBuffers()
//
//          If StartDrawing(SpriteOutput(#BubbleSprite)) Box(0, 0, xmaxScaled, ymaxScaled, $000000)
//
//              For i = 0 To n For j = 0 To n
//      u                            = Sin(i + v) + Sin(r * i + x) v =
//              Cos(i + v) + Cos(r * i + x) x =
//                  u + t Plot(hw + u * hw * 0.4, hh + v * hh * 0.4, RGB(i, j, 99)) Next Next StopDrawing() EndIf t +
//                  0.001 DisplaySprite(#BubbleSprite, 0, 0) ForEver EndIf EndIf



///-----------------------------------------------------------------------------------------
//
//Const xmax = 512,
//      ymax = 512 _Title "Bubble Universe - ESC to exit" ' from johnno at RCBasic forum 2022-11-14 Screen _NewImage(xmax,
//                                                                                                                   ymax,
//                                                                                                                   32)
//' ---------------
//' Paul Dunn posted this code but for SpecBAS in a facebook group.
//' It looked so cool that I had to  rewrite it in Naalaa 7. Marcus
//'
//' bplus QB64 Mod of RCB version by Johnno56 TAU = 6.283185307179586 n = 200 r =
//          TAU / 235 x = 0 y = 0 v = 0 t = 0 hw =
//              xmax / 2 hh =
//                  ymax / 2 Do Color _RGB32(0, 0, 0) Cls For i = 0 To n For j = 0 To n u =
//                      Sin(i + v) + Sin(r * i + x) v =
//                          Cos(i + v) + Cos(r * i + x) x =
//                              u + t Color _RGB(i, j, 99) PSet(hw + u * hw * 0.4, hh + v * hh * 0.4) Next Next t =
//                                  t + 0.001 ' slowed way way down from .025 _Display _Limit 30 Loop Until _KeyDown(27)




///-----------------------------------------------------------------------------------------
//Const xmax = 512,
//      ymax = 512 _Title "Bubble Universe - ESC to exit" ' from johnno at RCBasic forum 2022-11-14 Screen _NewImage(xmax,
//                                                                                                                   ymax,
//                                                                                                                   32)
//' ---------------
//' Paul Dunn posted this code but for SpecBAS in a facebook group.
//' It looked so cool that I had to  rewrite it in Naalaa 7. Marcus
//'
//' bplus QB64 Mod of RCB version by Johnno56 TAU = 6.283185307179586 n = 200 r =
//          TAU / 235 x = 0 y = 0 v = 0 t = 0 hw =
//              xmax / 2 hh =
//                  ymax / 2 Do Color _RGB32(0, 0, 0) Cls For i = 0 To n For j = 0 To n u =
//                      Sin(i + v) + Sin(r * i + x) v =
//                          Cos(i + v) + Cos(r * i + x) x =
//                              u + t Color _RGB(i, j, 99) PSet(hw + u * hw * 0.4, hh + v * hh * 0.4) Next Next t =
//                                  t + 0.001 ' slowed way way down from .025 _Display _Limit 30 Loop Until _KeyDown(27)
