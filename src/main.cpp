#include <iostream>
#include <ctime>
#include <easyx.h>
#include "../include/Utils.h"


// ������
int main() {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);	// ������ͼ����

	while (TRUE) {
		srand(time(nullptr));  // �������������

		// ��ʼ��Ϸ����
		startScreen();
	
		// ��Ϸ��ѭ��
		int finalScore = gameLoop();

		// ��������
		endScreen(finalScore);
	}

	closegraph();			// �رջ�ͼ����
	return 0;
}