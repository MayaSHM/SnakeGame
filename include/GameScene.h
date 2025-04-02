#pragma once
#include "Snake.h"
#include "Food.h"
#include "pairHash.h"
#include <unordered_set>
#include <string>
#include <windows.h>
#include <mmsystem.h> // ��Ҫ���� mmsystem ͷ�ļ�
#pragma comment(lib, "winmm.lib") // ���� winmm ��

// ����
class GameScene {
public:
	GameScene();

	// �ߣ��ƶ�
	void snakeMove();

	// ײ�����ж����ڸ�������֮ǰ�ж���
	bool isCollisionWithBody();

	// ȷ��ͷ����ײ�������ֱ�Ӹ�����ͷռ������
	void updateHeadCoor();

	// ײǽ�ж�
	bool isCollisionWithEdges();

	// ��ʳ���ж�
	bool isCollisionWithFood();

	void afterEatFoods();

	int getScore();

	auto getSnakeInst();

	// ʹ��˫�����ͼ��������
	void drawScreen();

	// ��Ӧ��Ϣ
	void onKeyDownMsg(ExMessage& msg);

private:
	Snake snake;
	Food food;
	int m_score;
	std::pair<int, int> prevHeadCoor;
	std::unordered_set<std::pair<int, int>, pairHash> prevAllCoor;
};
