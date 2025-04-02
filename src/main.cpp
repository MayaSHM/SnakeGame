#include <iostream>
#include <ctime>
#include <easyx.h>
#include "../include/Utils.h"


// 主函数
int main() {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);	// 创建绘图窗口

	while (TRUE) {
		srand(time(nullptr));  // 设置随机数种子

		// 开始游戏界面
		startScreen();
	
		// 游戏主循环
		int finalScore = gameLoop();

		// 结束画面
		endScreen(finalScore);
	}

	closegraph();			// 关闭绘图窗口
	return 0;
}