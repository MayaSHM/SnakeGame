#include "../include/Utils.h"

using hrclock = std::chrono::high_resolution_clock;

// ��ʼ����
void startScreen() {
	BeginBatchDraw();
	cleardevice();
	settextcolor(WHITE);
	settextstyle(120, 0, _T("Consolas"));
	RECT r = { 0, 0, WINDOW_WIDTH - 1, WINDOW_HEIGHT * 2 / 3 - 1 };
	drawtext(_T("̰ �� ��"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	settextcolor(WHITE);
	settextstyle(30, 0, _T("Consolas"));
	RECT r2 = { 0, WINDOW_HEIGHT / 3, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1 };
	drawtext(_T("���������ʼ����"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	EndBatchDraw();
	// �ȴ��û��������
	while (!_kbhit()) {
		Sleep(10);  // ���� CPU ռ�ù���
	}
	_getch();  // ��ȡ��������������뻺������
}

// ��Ϸ��ѭ��
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

		// �ȼ���Ƿ�ײ���壬�ٸ������꣬�ټ���Ƿ�ײǽ
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

		while (peekmessage(&msg, EX_KEY)) {  // peekmessage����easyx.h��������winuser.h
			scene.onKeyDownMsg(msg);
			flushmessage();
		}
		Sleep(10);
	}
	return scene.getScore();
}

// ��������
void endAnimation() {
	
}

// ��������
void endScreen(int score) {
	cleardevice();
	settextcolor(WHITE);
	settextstyle(100, 0, _T("Consolas"));
	RECT r = { 0, 0, WINDOW_WIDTH - 1, WINDOW_HEIGHT * 2 / 3 - 1 };
	drawtext(_T("��Ϸ����"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	settextcolor(WHITE);
	settextstyle(50, 0, _T("Consolas"));
	RECT r2 = { 0, WINDOW_HEIGHT * 1 / 3, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1 };
	TCHAR s[100];
	_stprintf_s(s, _T("���յ÷֣�%d"), score);		// �߰汾 VC �Ƽ�ʹ�� _stprintf_s ����
	drawtext(s, &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	settextcolor(WHITE);
	settextstyle(30, 0, _T("Consolas"));
	RECT r3 = { 0, WINDOW_HEIGHT * 1 / 2, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1 };
	drawtext(_T("����������¿�ʼ����"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// ��ջ�����
	while (_kbhit()) {
		_getch();  // _getch()һ��ֻ��ȡһ������
	}

	// �ȴ��û��������
	while (!_kbhit()) {
		Sleep(10);  // ���� CPU ռ�ù���
	}
	_getch();  // ��ȡ��������������뻺������
}

