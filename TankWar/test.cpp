#include <conio.h>
#include <graphics.h>

void drawHealthBar(int x, int y, int width, int height, int health) {
    // ���Ʊ���
    setfillcolor(LIGHTGRAY);
    bar(x, y, x + width, y + height);

    // ���ݵ�ǰ����ֵ����ǰ��
    int currentWidth = (width * health) / 100; // ����health��0��100֮���ֵ
    setfillcolor(RED);
    bar(x, y, x + currentWidth, y + height);
}

int main() {
    // ��ʼ��ͼ�δ���
    initgraph(640, 480);

    int health = 100;

    while (true) {
        // �����Ļ
        cleardevice();

        // ����Ѫ��
        drawHealthBar(50, 50, 200, 20, health);

        // ģ�⽡��ֵ�仯
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'w' && health < 100)
                health += 10; // ���ӽ���ֵ
            if (ch == 's' && health > 0)
                health -= 10; // ���ٽ���ֵ
            if (ch == 'q')
                break; // �˳�ѭ��
        }

        // �����ӳ�
        Sleep(100);
    }

    // �ر�ͼ�δ���
    closegraph();
    return 0;
}
