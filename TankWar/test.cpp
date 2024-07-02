#include <conio.h>
#include <graphics.h>

void drawHealthBar(int x, int y, int width, int height, int health) {
    // 绘制背景
    setfillcolor(LIGHTGRAY);
    bar(x, y, x + width, y + height);

    // 根据当前健康值绘制前景
    int currentWidth = (width * health) / 100; // 假设health是0到100之间的值
    setfillcolor(RED);
    bar(x, y, x + currentWidth, y + height);
}

int main() {
    // 初始化图形窗口
    initgraph(640, 480);

    int health = 100;

    while (true) {
        // 清空屏幕
        cleardevice();

        // 绘制血条
        drawHealthBar(50, 50, 200, 20, health);

        // 模拟健康值变化
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'w' && health < 100)
                health += 10; // 增加健康值
            if (ch == 's' && health > 0)
                health -= 10; // 减少健康值
            if (ch == 'q')
                break; // 退出循环
        }

        // 短暂延迟
        Sleep(100);
    }

    // 关闭图形窗口
    closegraph();
    return 0;
}
