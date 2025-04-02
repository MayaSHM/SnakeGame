#pragma once
#include "Snake.h"
#include "Food.h"
#include "pairHash.h"
#include <unordered_set>
#include <string>
#include <windows.h>
#include <mmsystem.h> // 需要包含 mmsystem 头文件
#pragma comment(lib, "winmm.lib") // 链接 winmm 库

// 场景
class GameScene {
public:
	GameScene();

	// 蛇，移动
	void snakeMove();

	// 撞身体判定（在更新坐标之前判定）
	bool isCollisionWithBody();

	// 确定头部不撞到身体后，直接更新蛇头占据坐标
	void updateHeadCoor();

	// 撞墙判定
	bool isCollisionWithEdges();

	// 吃食物判定
	bool isCollisionWithFood();

	void afterEatFoods();

	int getScore();

	auto getSnakeInst();

	// 使用双缓冲绘图处理闪屏
	void drawScreen();

	// 响应消息
	void onKeyDownMsg(ExMessage& msg);

private:
	Snake snake;
	Food food;
	int m_score;
	std::pair<int, int> prevHeadCoor;
	std::unordered_set<std::pair<int, int>, pairHash> prevAllCoor;
};
