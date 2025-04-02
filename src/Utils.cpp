#include "../include/Utils.h"

using hrclock = std::chrono::high_resolution_clock;

// 开始界面
void startScreen() {
	BeginBatchDraw();
	cleardevice();
	settextcolor(WHITE);
	settextstyle(120, 0, _T("Consolas"));
	RECT r = { 0, 0, WINDOW_WIDTH - 1, WINDOW_HEIGHT * 2 / 3 - 1 };
	drawtext(_T("贪 吃 蛇"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	settextcolor(WHITE);
	settextstyle(30, 0, _T("Consolas"));
	RECT r2 = { 0, WINDOW_HEIGHT / 3, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1 };
	drawtext(_T("按任意键开始……"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	EndBatchDraw();
	// 等待用户按任意键
	while (!_kbhit()) {
		Sleep(10);  // 避免 CPU 占用过高
	}
	_getch();  // 获取按键（并清空输入缓冲区）
}

// 游戏主循环
int gameLoop() {
	GameScene scene;
	ExMessage msg = { 0 };
	auto start = hrclock::now();
	while (TRUE) {
		scene.drawScreen();
		auto now = hrclock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);

		if (duration.count() >= SNAKE_SPEED) {
			scene.snakeMove();
			start = now;
		}

		// 先检查是否撞身体，再更新坐标，再检查是否撞墙
		if (scene.isCollisionWithBody()) {
			//std::cout << "body." << std::endl;
			break;
		}
		scene.updateHeadCoor();

		if (scene.isCollisionWithEdges()) {
			//std::cout << "edge." << std::endl;
			break;
		}

		scene.afterEatFoods();

		while (peekmessage(&msg, EX_KEY)) {  // peekmessage来自easyx.h，而不是winuser.h
			scene.onKeyDownMsg(msg);
			flushmessage();
		}
		Sleep(10);
	}
	return scene.getScore();
}

// 结束动画
void endAnimation() {
	
}

// 结束画面
void endScreen(int score) {
	cleardevice();
	settextcolor(WHITE);
	settextstyle(100, 0, _T("Consolas"));
	RECT r = { 0, 0, WINDOW_WIDTH - 1, WINDOW_HEIGHT * 2 / 3 - 1 };
	drawtext(_T("游戏结束"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	settextcolor(WHITE);
	settextstyle(50, 0, _T("Consolas"));
	RECT r2 = { 0, WINDOW_HEIGHT * 1 / 3, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1 };
	TCHAR s[100];
	_stprintf_s(s, _T("最终得分：%d"), score);		// 高版本 VC 推荐使用 _stprintf_s 函数
	drawtext(s, &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	settextcolor(WHITE);
	settextstyle(30, 0, _T("Consolas"));
	RECT r3 = { 0, WINDOW_HEIGHT * 1 / 2, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1 };
	drawtext(_T("按任意键重新开始……"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// 清空缓冲区
	while (_kbhit()) {
		_getch();  // _getch()一次只获取一个按键
	}

	// 等待用户按任意键
	while (!_kbhit()) {
		Sleep(10);  // 避免 CPU 占用过高
	}
	_getch();  // 获取按键（并清空输入缓冲区）
}

