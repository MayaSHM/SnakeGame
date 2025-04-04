#include "../include/GameScene.h"

GameScene::GameScene() : m_score(0) {
	auto nodes = snake.getNodes();
	prevHeadCoor = std::make_pair(nodes[0].getX(), nodes[0].getY());
	for (size_t i = 0; i < nodes.size(); i++)
	{
		prevAllCoor.insert(std::make_pair(nodes[i].getX(), nodes[i].getY()));
	}
}

// 蛇，移动
void GameScene::snakeMove() {
	auto prevTail = snake.getNodes().back();
	auto prevTailCoor = std::make_pair(prevTail.getX(), prevTail.getY());
	snake.move();
	prevAllCoor.erase(prevTailCoor);  // 移动后直接清除之前的尾巴坐标，方便判断头部有没有撞到身体
}

// 撞身体判定（在更新坐标之前判定）
bool GameScene::isCollisionWithBody() {
	auto currHead = snake.getNodes().front();
	auto currHeadCoor = std::make_pair(currHead.getX(), currHead.getY());
	if (prevAllCoor.count(currHeadCoor) > 0 && currHeadCoor != prevHeadCoor) {
		PlaySound(L".\\resource\\maou_se_battle_explosion06.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		return TRUE;
	}
	else {
		return FALSE;
	}
}

// 确定头部不撞到身体后，直接更新蛇头占据坐标
void GameScene::updateHeadCoor() {
	auto currHead = snake.getNodes().front();
	prevHeadCoor = std::make_pair(currHead.getX(), currHead.getY());
	prevAllCoor.insert(prevHeadCoor);
}

// 撞墙判定
bool GameScene::isCollisionWithEdges() {
	if (prevHeadCoor.first  < 0 + EDGE_WIDTH || prevHeadCoor.first  >= WINDOW_WIDTH -  EDGE_WIDTH ||
		prevHeadCoor.second < 0 + EDGE_WIDTH || prevHeadCoor.second >= WINDOW_HEIGHT - EDGE_WIDTH) {
		//PlaySound(L".\\resource\\maou_se_battle_explosion06.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_ASYNC | SND_NODEFAULT | SND_RESOURCE);
		return TRUE;
	}
	else {
		return FALSE;
	}
}

// 吃食物判定
bool GameScene::isCollisionWithFood() {
	return prevHeadCoor.first == food.getX() && prevHeadCoor.second == food.getY();
}

// 吃到食物后，更新蛇长度，并重新生成食物
void GameScene::afterEatFoods() {
	if (isCollisionWithFood()) {
		snake.grow();
		food.regenerate(prevAllCoor);
		m_score += 1;
		// 播放音效
		//PlaySound(L".\\resource\\se3.wav", NULL, SND_ASYNC | SND_NODEFAULT);
		PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_ASYNC | SND_NODEFAULT | SND_RESOURCE);
	}
}

int GameScene::getScore() {
	return m_score;
}

auto GameScene::getSnakeInst() {
	return &snake;
}

// 使用双缓冲绘图处理闪屏
void GameScene::drawScreen() {
	BeginBatchDraw();
	cleardevice();
	// 绘制背景
	setfillcolor(WHITE);
	fillrectangle(0, 0, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1);
	setfillcolor(BLACK);
	fillrectangle(EDGE_WIDTH, EDGE_WIDTH, WINDOW_WIDTH - EDGE_WIDTH, WINDOW_HEIGHT - EDGE_WIDTH);
	snake.draw();
	food.draw();
	// 显示当前分数
	TCHAR s[100];
	RECT r = { 0, 0, WINDOW_WIDTH - 1, EDGE_WIDTH - 1 };
	_stprintf_s(s, _T("当前得分：%d"), m_score);		// 高版本 VC 推荐使用 _stprintf_s 函数
	settextstyle(20, 0, _T("Consolas"));
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	drawtext(s, &r, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	EndBatchDraw();
}

// 响应消息
void GameScene::onKeyDownMsg(ExMessage& msg) {
	if (msg.message == WM_KEYDOWN) {  // 响应按键消息
		if (msg.vkcode == VK_UP || msg.vkcode == VK_DOWN || msg.vkcode == VK_LEFT || msg.vkcode == VK_RIGHT) {
			//std::cout << static_cast<int>(msg.vkcode) << std::endl;
			// 由于peekmessage的非阻塞性质，快速按键将导致方向快速改变
			// 因此需要根据蛇头后一节（蛇“脖子”）的位置来判断可以前进的方向
			auto nodes = snake.getNodes();
			Sprite head = nodes[0];
			Sprite neck = nodes[1];
			std::string currDir = "RIGHT";
			if (head.getX() > neck.getX() && head.getY() == neck.getY()) {
				currDir = "RIGHT";
			}
			else if (head.getX() < neck.getX() && head.getY() == neck.getY()) {
				currDir = "LEFT";
			}
			else if (head.getY() > neck.getY() && head.getX() == neck.getX()) {
				currDir = "DOWN";
			}
			else if (head.getY() < neck.getY() && head.getX() == neck.getX()) {
				currDir = "UP";
			}
			//std::cout << currDir << std::endl;
			//if (msg.vkcode == VK_UP && snake.getDir() != VK_DOWN) {
			//	snake.setDir(msg.vkcode);  // virtual key code
			//}
			//else if (msg.vkcode == VK_DOWN && snake.getDir() != VK_UP) {
			//	snake.setDir(msg.vkcode);  // virtual key code
			//}
			//else if (msg.vkcode == VK_LEFT && snake.getDir() != VK_RIGHT) {
			//	snake.setDir(msg.vkcode);  // virtual key code
			//}
			//else if (msg.vkcode == VK_RIGHT && snake.getDir() != VK_LEFT) {
			//	snake.setDir(msg.vkcode);  // virtual key code
			//}

			if (msg.vkcode == VK_UP && currDir != "DOWN") {
				snake.setDir(msg.vkcode);  // virtual key code
			}
			else if (msg.vkcode == VK_DOWN && currDir != "UP") {
				snake.setDir(msg.vkcode);  // virtual key code
			}
			else if (msg.vkcode == VK_LEFT && currDir != "RIGHT") {
				snake.setDir(msg.vkcode);  // virtual key code
			}
			else if (msg.vkcode == VK_RIGHT && currDir != "LEFT") {
				snake.setDir(msg.vkcode);  // virtual key code
			}
		}
	}
	flushmessage();
}
