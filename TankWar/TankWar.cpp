#include <graphics.h>
#include <iostream>
#include <stdio.h>

#define WIDTH 800  // 窗口宽度, 像素
#define HEIGHT 600 // 窗口高度, 像素

/******************************************
 * 地图数据
 ******************************************/

#define X_NUM 16 // 宽度划分为16个方格
#define Y_NUM 12 // 高度划分为12个方格

int dx = 68; // 三个按键之间的间隔
int dy = 40; // 按键的高度

#define HELP_X 160 + dx // 帮助按键的左上角的x坐标
#define HELP_Y 270      // y坐标

#define SETTING_X HELP_X + dx * 2// 设置按键的左上角的x坐标
#define SETTING_Y HELP_Y

#define START_X HELP_X + dx * 4
#define START_Y HELP_Y

// 800 / 50 = 16, 600 / 50 = 12
// 0表示空地, 1表示砖墙(wall_1, 可以摧毁), 2表示铁墙(wall_2, 不可以摧毁)
// 10表示玩家, 100表示普通敌人, 200表示BOSS, 一个坦克占1个格子
// 每一个砖块占一格

// 第一关, 普通
extern int Map1[X_NUM][Y_NUM] = {
    {},

};

// 第二关, BOSS
extern int Map2[X_NUM][Y_NUM] = {

};

// 显示操作坦克的方法
void show_help() {
    setlinecolor(WHITE); // 框线的颜色: 白色
    setfillcolor(BLACK); // 框内填充的颜色: 黑色
    fillrectangle(160, 350, 160 + 480, 350 + 40);
    settextstyle(25, 0, _T("微软雅黑"));
    outtextxy(170 + 60, 360, _T("上:W 下:S 左:A 右:D 攻击:Space 暂停:P"));
}

// 显示初始界面
void init() {

    // 绘制游戏窗口 宽800高600像素

    initgraph(WIDTH, HEIGHT);

    IMAGE logo;
    // 加载logo
    loadimage(&logo, _T("logo.png"), 480, 54);

    // 显示logo
    putimage(160, 200, &logo);

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
    while (true) {
        mouse = GetMouseMsg(); // 获取当前鼠标信息
        switch (mouse.uMsg) {
        case WM_MOUSEMOVE: 
            if ((mouse.x >= HELP_X && mouse.x <= HELP_X + dx) && (mouse.y >= HELP_Y && mouse.y <= HELP_Y + dy)) {
                show_help(); // 鼠标悬浮到"帮助"上时, 显示帮助信息
            } else {         
                solidrectangle(160, 350, 160 + 480, 350 + 40);// 把帮助信息覆盖涂黑, 等效于不显示帮助信息
            }
            break;
        case WM_LBUTTONDOWN:
            if ((mouse.x >= START_X && mouse.x <= START_X + dx) && (mouse.y >= START_Y && mouse.y <= START_Y + dy)) {
                std::cout << "1 ";
            }


            break;
        }
    }
}

// 运行游戏
void play() {
    // 加载并显示地图
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
    init();

    // 运行游戏
    play();

    // 游戏结束
    // game_over();

    system("pause");
    return 0;
}
