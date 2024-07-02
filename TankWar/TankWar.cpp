#include <graphics.h>
#include <iostream>
int main() {
	// 创建画布
	initgraph(800, 600); // 画布宽高比4:3


	// 显示主界面
	IMAGE player_img; // 玩家操作的坦克
	loadimage(&player_img, _T("tank_player_down.png"), 50, 50);
	int cnt = 0;
	for (int i = 0; i <= 800 - 50; i += 50) {
		for (int j = 0; j <= 600 - 50; j += 50) {
			putimage(i, j, &player_img);
			cnt++;
		}
	}
	std::cout << cnt << '\n';
	system("pause");
	return 0;
}