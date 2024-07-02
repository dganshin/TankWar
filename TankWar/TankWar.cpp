
#include <conio.h>
#include <graphics.h>
#include <iostream>
#include <stdio.h>

#define WIDTH 800  // 窗口宽度, 像素
#define HEIGHT 600 // 窗口高度, 像素

#define X_NUM 16 // 宽度方格
#define Y_NUM 12 // 高度方格

// 坦克结构体
struct Tank_s {
    int id;        // 10: 玩家, 100: 普通敌人, 200: BOSS
    int x, y;      // 在地图上的坐标
    int health;    // 血量
    int atk;       // 炮弹攻击力
    int speed;     // 移动速度
    int direction; // 坦克当前朝向
    bool is_alive = true;
};

// 炮弹结构体
struct Bullet_s {
    int akt;   // 炮弹伤害
    int speed; // 炮弹速度
};

/******************************************
 * 地图数据
 ******************************************/

/******************************************
 * 注意, 绘图的x对应数组的y
 *******************************************/
// 800 / 50 = 16, 600 / 50 = 12
// 0表示空地, 1表示砖墙(wall_1, 可以摧毁), 2表示铁墙(wall_2, 不可以摧毁)
// 10表示玩家, 100表示普通敌人, 200表示BOSS, 一个坦克占1个格子
// 每一个砖块占一格
// 第一关, 普通
int Map1[X_NUM][Y_NUM] = {
    {1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1},
    {100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {2, 2, 2, 1, 2, 1, 2, 1, 1, 2, 1, 1},
    {2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 1, 2, 1, 2, 1, 2, 2, 2, 1},
    {100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 2, 1, 2, 2, 2, 1, 2, 1, 1, 1},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10},
    {2, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1},
    {1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1},
    {1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1},
    {100, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1},
    {2, 2, 2, 2, 2, 1, 1, 1, 2, 1, 2, 1},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2}};

// 第二关, BOSS
int Map2[X_NUM][Y_NUM] = {

};

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

bool ready_play = false;  // 是否可以开始游戏
bool is_gameover = false; // 是否结束当前游戏
bool is_setting = false;  // 是否处于设置界面

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

void init_map() {
    IMAGE Player, Enemy_1, Enemy_2, Wall_1, Wall_2;

    loadimage(&Wall_1, _T("wall_1.png"), 50, 50);
    loadimage(&Wall_2, _T("wall_2.png"), 50, 50);
    loadimage(&Player, _T("tank_player_1_U.png"), 50, 50);
    loadimage(&Enemy_1, _T("tank_enemy_1_D.png"), 50, 50);
    loadimage(&Enemy_2, _T("tank_enemy_2_D.png"), 50, 50);

    Tank_s my_tank = {10, 0, 0, 200, 100, 100, UP, true};
    Tank_s enemy_1 = {100, 0, 0, 200, 100, 100, DOWN, true};
    Tank_s enemy_2 = {200, 0, 0, 500, 200, 150, DOWN, true};
    // 遍历地图数组, 显示墙和坦克
    for (int i = 0; i < X_NUM; i++) {
        for (int j = 0; j < Y_NUM; j++) {
            if (Map1[i][j] == 1) {
                putimage(i * 50, j * 50, &Wall_1);
            } else if (Map1[i][j] == 2) {
                putimage(i * 50, j * 50, &Wall_2);
            } else if (Map1[i][j] == 10) {
                putimage(i * 50, j * 50, &Player);
                my_tank.x = i;
                my_tank.y = j;
                my_tank.direction = UP;
            } else if (Map1[i][j] == 100) {
                putimage(i * 50, j * 50, &Enemy_1);
                enemy_1.x = i;
                enemy_1.y = j;
                enemy_1.direction = DOWN;
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
}

// 运行游戏
void play() {
    // 加载并显示地图
    init_map();
    /*while (true) {
        if (is_gameover) {
            break;
        }
    }*/
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
    if (ready_play)
        play();

    // 游戏结束
    // game_over();

    system("pause");
    return 0;
}
