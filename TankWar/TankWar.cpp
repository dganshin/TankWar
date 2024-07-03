﻿#include <conio.h>
#include <graphics.h>
#include <iostream>
#include <stdio.h>
#include <time.h>

#define WIDTH 800  // 窗口宽度, 像素
#define HEIGHT 600 // 窗口高度, 像素
#define X_NUM 16   // 宽度方格
#define Y_NUM 12   // 高度方格

#define D 50 // 全局变量 一个方格的像素差距

// 坦克结构体
struct Tank_s {
    int id;               // 100: 玩家, 10: 普通敌人, 20: BOSS
    int x, y;             // 在地图上的像素坐标 x:0-800, y:0-600
    int X, Y;             // 相对坐标
    int health;           // 血量
    int atk;              // 炮弹攻击力
    int speed;            // 移动速度
    int direction;        // 坦克当前朝向
    bool is_alive = true; // 坦克是否存活
};

// 炮弹结构体
struct Bullet_s {
    int x, y;           // 炮弹坐标(最小限度25)
    int speed;          // 炮弹速度
    int direction;      // 炮弹方向
    bool status = true; // 炮弹状态, 是否能显示
    int lx, ly;         // lastx, lasty
};

/******************************************
 * 地图数据
 ******************************************/

// 800 / D = 16, 600 / D = 12
// 0表示空地, 1表示砖墙(wall_1, 可以摧毁), 2表示铁墙(wall_2, 不可以摧毁)
// 10表示玩家, 100表示普通敌人, 200表示BOSS, 一个坦克占1个格子
// 每一个砖块占一格
// 第一关, 普通

int Map1[X_NUM][Y_NUM] = {
    {1, 1, 1, 1, 2, 0, 1, 1, 1, 1, 2, 1},
    {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {2, 2, 2, 1, 2, 1, 0, 1, 1, 2, 1, 1},
    {2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 1, 2, 1, 0, 1, 2, 2, 2, 1},
    {10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 1, 2, 2, 0, 1, 2, 1, 1, 1},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100},
    {2, 2, 2, 1, 1, 2, 0, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 1, 2, 0, 1, 1, 2, 1, 1, 2, 1},
    {1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 2, 1},
    {10, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1},
    {2, 2, 2, 2, 2, 0, 1, 1, 2, 1, 2, 1},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}};

// int Map1[X_NUM][Y_NUM] = {
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 100, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

// 第二关, BOSS
int Map2[X_NUM][Y_NUM] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 100, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

// 方向
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

// 全局条件判断
bool ready_play = false;  // 是否可以开始游戏
bool is_gameover = false; // 是否结束当前游戏
bool is_setting = false;  // 是否处于设置界面

// 图形界面微调参数
int dx = 68; // 三个按键之间的间隔
int dy = 40; // 按键的高度

#define HELP_X 160 + dx // 帮助按键的左上角的x坐标
#define HELP_Y 270      // y坐标

#define SETTING_X HELP_X + dx * 2 // 设置按键的左上角的x坐标
#define SETTING_Y HELP_Y

#define START_X HELP_X + dx * 4
#define START_Y HELP_Y

// 显示帮助(操作方法)
void show_help() {
    setlinecolor(WHITE); // 框线的颜色: 白色
    setfillcolor(BLACK); // 框内填充的颜色: 黑色
    fillrectangle(160, 350, 160 + 480, 350 + 40);
    settextstyle(25, 0, _T("微软雅黑"));
    outtextxy(170 + 60, 360, _T("上:W 下:S 左:A 右:D 攻击:Space 暂停:P"));
}

// 初始化地图
void init_map() {
    IMAGE Wall_1, Wall_2; // 图像指针

    // 载入墙体图片
    loadimage(&Wall_1, _T("wall_1.png"), D, D);
    loadimage(&Wall_2, _T("wall_2.png"), D, D);

    // 遍历地图数组, 绘制地图
    for (int i = 0; i < X_NUM; i++) {
        for (int j = 0; j < Y_NUM; j++) {
            if (Map1[i][j] == 1) {
                putimage(i * D, j * D, &Wall_1);
            } else if (Map1[i][j] == 2) {
                putimage(i * D, j * D, &Wall_2);
            }
        }
    }
}

void setting();

// 显示初始界面
void init_menu() {

    // 绘制游戏窗口 宽800高600像素
    initgraph(WIDTH, HEIGHT);

    IMAGE logo;

    // 加载logo
    loadimage(&logo, _T("logo.png"), 480, 54); // 特定数据请不要改动

    // 显示logo
    putimage(160, 200, &logo); // 特定数据

    // 显示"说明", "设置", "开始"

    setlinecolor(WHITE); // 框线的颜色: 白色
    setfillcolor(BLACK); // 框内填充的颜色: 黑色

    settextstyle(25, 0, _T("微软雅黑"));

    // 绘制帮助选项框(x1, y1, x2, y2)
    int dx = 68; // 三个按键之间的间隔
    int dy = 40; // 按键的高度
    fillrectangle(HELP_X, HELP_Y, HELP_X + dx, HELP_Y + dy);
    outtextxy(HELP_X + 10, HELP_Y + 10, _T("帮助"));

    // 绘制设置选项框
    fillrectangle(SETTING_X, SETTING_Y, SETTING_X + dx, SETTING_Y + dy);
    outtextxy(SETTING_X + 10, SETTING_Y + 10, _T("设置"));

    // 绘制开始选项框
    fillrectangle(START_X, START_Y, START_X + dx, START_Y + dy);
    outtextxy(START_X + 10, START_Y + 10, _T("开始"));

    // 当鼠标选停在帮助时, 显示操作方法
    MOUSEMSG mouse;
    while (true && !ready_play && !is_setting) {
        mouse = GetMouseMsg(); // 获取当前鼠标信息
        switch (mouse.uMsg) {
        case WM_MOUSEMOVE:
            // 悬浮"帮助"
            if ((mouse.x >= HELP_X && mouse.x <= HELP_X + dx) && (mouse.y >= HELP_Y && mouse.y <= HELP_Y + dy)) {
                show_help(); // 鼠标悬浮到"帮助"上时, 显示帮助信息
            } else {
                solidrectangle(160, 350, 160 + 480, 350 + 40); // 把帮助信息覆盖涂黑, 等效于不显示帮助信息
            }
            break;
        case WM_LBUTTONDOWN:
            // 点击开始
            if ((mouse.x >= START_X && mouse.x <= START_X + dx) && (mouse.y >= START_Y && mouse.y <= START_Y + dy)) {
                ready_play = true;
                cleardevice(); // 清屏
                break;
            }
            // 点击设置
            else if ((mouse.x >= SETTING_X && mouse.x <= SETTING_X + dx) && mouse.y >= SETTING_Y && mouse.y <= SETTING_Y + dy) {
                is_setting = true;
                cleardevice();
                setting();
                break;
            }
            break;
        }
    }
}

void setting() {

    // 设置完成之后回到主界面

    init_menu();
    is_setting = false;
}

// 封装绘图函数
void Putimage(Tank_s tank_s, IMAGE image[]) {
    putimage(tank_s.x, tank_s.y, &image[tank_s.direction]);
}

ExMessage key;

/**********************************************************************
 * 重难点 碰撞检测与边界判定
 ***********************************************************************/

bool moveable(int map[][Y_NUM], Tank_s tank) {
    // 边界区域
    /*if (tank.x - tank.speed < 0 || tank.y - tank.speed < 0 || tank.x + D + tank.speed > 800 || tank.y + D + tank.speed > 600)
        return false;*/
    // 试探是否能向direction方向移动
    switch (tank.direction) {
    case UP: {
        if (tank.y - tank.speed < 0)
            return false;
        int tx = tank.x / D * D;
        int ty = tank.y / D * D;
        int TX = tx / D;
        int TY = ty / D - 1;
        ty = TY * D;
        // std::cout << "TXTYT" << TX << " " << TY << '\n';
        // std::cout << "tx ty " << tx << " " << ty << '\n';
        if (map[TX][TY] <= 20 && map[TX][TY] > 0) {
            if (ty + D >= tank.y && (tank.x < tx + D && tank.x >= tx))
                return false;
        }
        if (map[TX + 1][TY] <= 20 && map[TX + 1][TY] > 0) {
            if (ty + D >= tank.y && (tank.x < (TX + 1) * D && tank.x + D > (TX + 1) * D))
                return false;
        }
        break;
    }
    case DOWN: {
        if (tank.y + tank.speed + D > 600)
            return false;
        int tx = tank.x / D * D;
        int ty = tank.y / D * D;
        int TX = tx / D;
        int TY = ty / D + 1;
        ty = TY * D;

        if (map[TX][TY] <= 20 && map[TX][TY] > 0) {
            if (tank.y + D >= (TY * D) && (tank.x < (TX * D) + D && tank.x + D > (TX * D)))
                return false;
        }
        if (map[TX + 1][TY] <= 20 && map[TX + 1][TY] > 0) {
            if (tank.y + D >= ty && (tank.x < (TX + 1) * D + D && tank.x + D > (TX + 1) * D))
                return false;
        }
        break;
    }

    case LEFT: {
        if (tank.x - tank.speed < 0)
            return false;
        int tx = tank.x / D * D;
        int ty = tank.y / D * D;
        int TX = tx / D - 1;
        int TY = ty / D;
        tx = TX * D;

        if (map[TX][TY] <= 20 && map[TX][TY] > 0) {
            if (tank.x <= tx + D && (ty - D < tank.y && ty > tank.y - D))
                return false;
        }

        if (map[TX][TY + 1] <= 20 && map[TX][TY + 1] > 0) {
            if (tank.x <= tx + D && ((TY + 1) * D - D < tank.y && (TY + 1) * D > tank.y - D))
                return false;
        }

        break;
    }

    case RIGHT: {
        if (tank.x + tank.speed + D > 800)
            return false;
        int tx = tank.x / D * D;
        int ty = tank.y / D * D;
        int TX = tx / D + 1;
        int TY = ty / D;
        if (map[TX][TY] <= 20 && map[TX][TY] > 0) {
            if (tank.x + D >= tx && (ty - D < tank.y && ty > tank.y - D))
                return false;
        }
        if (map[TX][TY + 1] <= 20 && map[TX][TY + 1] > 0) {
            if (tank.x + D >= tx && ((TY + 1) * D - D < tank.y && (TY + 1) * D > tank.y - D))
                return false;
        }

        break;
    }
    default:
        break;
    }
    return true;
}

#define Enemy_Num 4 // 敌人数量

// 运行游戏
void play() {
    // 加载并显示地图
    init_map();
    // 声明我方坦克和敌方坦克的图像指针
    IMAGE my_tank[4], enemy_tank_1[4], enemy_tank_2[4], my_bullet;

    // 加载我方坦克图像
    loadimage(&my_tank[UP], _T("tank_player_1_U.png"), D, D);
    loadimage(&my_tank[DOWN], _T("tank_player_1_D.png"), D, D);
    loadimage(&my_tank[LEFT], _T("tank_player_1_L.png"), D, D);
    loadimage(&my_tank[RIGHT], _T("tank_player_1_R.png"), D, D);

    // 加载敌方普通坦克图像
    loadimage(&enemy_tank_1[UP], _T("tank_enemy_1_U.png"), D, D);
    loadimage(&enemy_tank_1[DOWN], _T("tank_enemy_1_D.png"), D, D);
    loadimage(&enemy_tank_1[LEFT], _T("tank_enemy_1_L.png"), D, D);
    loadimage(&enemy_tank_1[RIGHT], _T("tank_enemy_1_R.png"), D, D);

    // 加载敌方BOSS坦克图像
    loadimage(&enemy_tank_2[UP], _T("tank_enemy_2_U.png"), D, D);
    loadimage(&enemy_tank_2[DOWN], _T("tank_enemy_2_D.png"), D, D);
    loadimage(&enemy_tank_2[LEFT], _T("tank_enemy_2_L.png"), D, D);
    loadimage(&enemy_tank_2[RIGHT], _T("tank_enemy_2_R.png"), D, D);

    // 加载子弹图像
    loadimage(&my_bullet, _T("bullet.png"), 10, 10);

    // 初始化我方坦克
    Tank_s my_tank_s;
    for (int i = 0; i < X_NUM; i++) {
        for (int j = 0; j < Y_NUM; j++) {
            if (Map1[i][j] == 100) {
                my_tank_s = {100, i * D, j * D, i, j, 100, 100, 10, UP, true};
            }
        }
    }

    // 敌方坦克
    Tank_s enemy_tank_1_s[Enemy_Num];
    IMAGE enemy_bullet[Enemy_Num];

    // 初始化位置
    int cnt = 0;
    for (int i = 0; i < X_NUM; i++) {
        for (int j = 0; j < Y_NUM; j++) {
            if (Map1[i][j] == 10) {
                enemy_tank_1_s[cnt++] = {10, i * D, j * D, i, j, 100, 100, 10, DOWN, true};
            }
        }
    }
    // cnt--;
    for (int i = 0; i < cnt; i++) {
        Putimage(enemy_tank_1_s[i], enemy_tank_1);
    }

    // 显示我方坦克图像
    Putimage(my_tank_s, my_tank);

    // 初始化我方子弹
    Bullet_s my_bullet_s = {800, 600, 25, UP, true};

    while (true) {

        // 热键检测
        if (peekmessage(&key, EX_KEY)) {

            /***************
             * debug
             *************/
            // std::cout << "(" << my_tank_s.x << "," << my_tank_s.y << ")" << '\n';

            if (key.message == WM_KEYDOWN || key.message == WM_KEYUP) {
                switch (key.vkcode) {
                case 'W': {
                    // 方向切换到向上
                    my_tank_s.direction = UP;
                    Putimage(my_tank_s, my_tank);

                    // 判断是否能向上走一格
                    if (moveable(Map1, my_tank_s)) {
                        // 消除原来的图像
                        solidrectangle(my_tank_s.x, my_tank_s.y, my_tank_s.x + D - 1, my_tank_s.y + D - 1);
                        // 改变我方坦克坐标
                        my_tank_s.y -= my_tank_s.speed;
                        // 重新绘图
                        Putimage(my_tank_s, my_tank);
                    }
                    break;
                }
                case 'A': {
                    // 方向切换到向左
                    my_tank_s.direction = LEFT;
                    Putimage(my_tank_s, my_tank);
                    // 判断是否能向左走
                    if (moveable(Map1, my_tank_s)) {
                        // 消除原来的图像
                        solidrectangle(my_tank_s.x, my_tank_s.y, my_tank_s.x + D - 1, my_tank_s.y + D - 1);
                        // 改变我方坦克坐标
                        my_tank_s.x -= my_tank_s.speed;
                        // 重新绘图
                        Putimage(my_tank_s, my_tank);
                    }
                    break;
                }

                    // break;
                case 'S': {
                    // 方向切换到向下
                    my_tank_s.direction = DOWN;
                    Putimage(my_tank_s, my_tank);
                    // 判断是否能向下走
                    if (moveable(Map1, my_tank_s)) {
                        // 消除原来的图像
                        solidrectangle(my_tank_s.x, my_tank_s.y, my_tank_s.x + D, my_tank_s.y + D);
                        // 改变我方坦克坐标
                        my_tank_s.y += my_tank_s.speed;
                        // 重新绘图
                        Putimage(my_tank_s, my_tank);
                    }
                    break;
                }
                case 'D': {
                    // 方向切换到向右
                    my_tank_s.direction = RIGHT;
                    Putimage(my_tank_s, my_tank);
                    // 判断是否能向右走
                    if (moveable(Map1, my_tank_s)) {
                        // 消除原来的图像
                        solidrectangle(my_tank_s.x, my_tank_s.y, my_tank_s.x + D, my_tank_s.y + D);
                        // 改变我方坦克坐标
                        my_tank_s.x += my_tank_s.speed;
                        // 重新绘图
                        Putimage(my_tank_s, my_tank);
                    }
                    break;
                }

                case ' ': { // 开火
                    my_bullet_s.status = true;
                    my_bullet_s.direction = my_tank_s.direction;
                    switch (my_bullet_s.direction) {
                    case UP: {
                        my_bullet_s.x = my_tank_s.x / D * D;
                        my_bullet_s.y = my_tank_s.y / D * D;

                        break;
                    }
                    case DOWN: {
                        my_bullet_s.x = my_tank_s.x / D * D;
                        my_bullet_s.y = (my_tank_s.y / D + 1) * D;
                        break;
                    }
                    case LEFT: {
                        my_bullet_s.x = my_tank_s.x / D * D;
                        my_bullet_s.y = (my_tank_s.y / D) * D;
                        break;
                    }
                    case RIGHT: {
                        my_bullet_s.x = (my_tank_s.x / D + 1) * D;
                        my_bullet_s.y = (my_tank_s.y / D) * D;
                        break;
                    }
                    }
                }
                }
            }
        }

        // 炮弹飞行
        if (my_bullet_s.status) {
            putimage(my_bullet_s.x + 18, my_bullet_s.y + 18, &my_bullet);

            my_bullet_s.lx = my_bullet_s.x;
            my_bullet_s.ly = my_bullet_s.y;

            switch (my_bullet_s.direction) {
            case UP: {

                my_bullet_s.y -= my_bullet_s.speed;
                break;
            }
            case DOWN: {

                my_bullet_s.y += my_bullet_s.speed;
                break;
            }
            case LEFT: {

                my_bullet_s.x -= my_bullet_s.speed;
                break;
            }
            case RIGHT: {

                my_bullet_s.x += my_bullet_s.speed;
                break;
            }
            default:
                break;
            }
            Sleep(20);

            // 我方子弹
            if (my_bullet_s.x <= 800 && my_bullet_s.x >= 0 - D && my_bullet_s.y <= 600 && my_bullet_s.y >= 0 - D) {
                solidrectangle(my_bullet_s.lx + 18, my_bullet_s.ly + 18, my_bullet_s.lx + 10 + 18, my_bullet_s.ly + 10 + 18);

                if (Map1[my_bullet_s.x / D][my_bullet_s.y / D] == 1) { // 消除砖墙

                    Map1[my_bullet_s.x / D][my_bullet_s.y / D] = 0;
                    solidrectangle(my_bullet_s.x / D * D, my_bullet_s.y / D * D, my_bullet_s.x / D * D + D, my_bullet_s.y / D * D + D);
                    my_bullet_s.status = false;
                } else if (Map1[my_bullet_s.x / D][my_bullet_s.y / D] == 2) { // 无法消除, 子弹湮灭

                    my_bullet_s.status = false;
                } else if (Map1[my_bullet_s.x / D][my_bullet_s.y / D] == 10) {
                    solidrectangle(my_bullet_s.x / D * D, my_bullet_s.y / D * D, my_bullet_s.x / D * D + D, my_bullet_s.y / D * D + D);
                }
            }

            // 敌方炮弹
        }
    }
}

// 游戏结束
void game_over() {
    // 重新绘图
    initgraph(WIDTH, HEIGHT);

    // 显示gameover
    IMAGE gameover;
    loadimage(&gameover, _T("game_over.bmp"), 204, 132);
    putimage(298, 180, &gameover);

    // 判断是否胜利
}

int main() {
    // 显示初始界面
    init_menu();

    // 运行游戏
    if (ready_play) {
        play();
        // std ::cout << "111";
    }

    // 游戏结束
    // game_over();

    system("pause");
    return 0;
}
