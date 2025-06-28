#include <graphics.h>
#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include "atlas.h"
#include "animation.h"
#include "Actor.h"
#include "Platform.h"
#include "SceneManager.h"
#include "MenuScene.h"
#include "GameScene.h"
static const int windowWidth = 1280;
static const int windowHeight = 720;
static const int FPS = 60;

Atlas atlas_player_idle_left;
Atlas atlas_player_idle_right;
Atlas atlas_player_run_left;
Atlas atlas_player_run_right;

Atlas atl_test;
Animation ani_test;

Platform* platform = nullptr;
Platform* platform2 = nullptr;
Actor* player = nullptr;

SceneManager& manager = SceneManager::GetInstance();
MenuScene* menu = nullptr;
GameScene* game = nullptr;

void load_resources() {
    atlas_player_idle_left.load_from_file(_T("res/img/warrior_idle_left_%d.png"), 4);
    atlas_player_idle_right.load_from_file(_T("res/img/warrior_idle_right_%d.png"), 4);
    atlas_player_run_left.load_from_file(_T("res/img/warrior_walk_left_%d.png"), 8);
    atlas_player_run_right.load_from_file(_T("res/img/warrior_walk_right_%d.png"), 8);
    player = new Actor();
    platform = new Platform(Vector2(100, 400), Vector2(800, 100));
    platform2 = new Platform(Vector2(100, 200), Vector2(800, 30));
    game = new GameScene();
    game->addObject(player);
    game->addObject(platform);
    game->addObject(platform2);
    
    manager.set_current_scene(game);
    manager.switchTo(game);
}

/*
 * @brief 已经实现功能：玩家移动（四方向）、动画图集类
 * 下一步实现：背景、小型平台、加入重力场、边界检测、平台碰撞检测
 */

int main()
{
    ExMessage msg;
    initgraph(windowWidth, windowHeight, 1);
    setbkcolor(WHITE);
    load_resources();
    switch_keyboard();


    BeginBatchDraw();
    while (true)
    {
        DWORD frame_start_ticks = GetTickCount();
        // get message
        while (peekmessage(&msg)) {
            //player->input(msg);
            manager.input(msg);
        }
        static DWORD last_ticks = GetTickCount();
        DWORD current_ticks = GetTickCount();
        DWORD delta_ticks = current_ticks - last_ticks;
        // update
        //player->update(delta_ticks);
        manager.update(delta_ticks);
        
        last_ticks = current_ticks;

        cleardevice();
        // draw or render
        /*player->render();
        platform->render();*/
        manager.render();

        FlushBatchDraw();

        DWORD frame_end_ticks = GetTickCount();
        DWORD frame_delta_ticks = frame_end_ticks - frame_start_ticks;
 
        if (frame_delta_ticks < 1000 / FPS)
            Sleep(1000 / FPS - frame_delta_ticks);
    }
    EndBatchDraw();
    closegraph();

    // clear resources

    return 0;
}
