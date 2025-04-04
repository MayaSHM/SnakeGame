#include "../include/GameScene.h"

GameScene::GameScene() : m_score(0) {
	auto nodes = snake.getNodes();
	prevHeadCoor = std::make_pair(nodes[0].getX(), nodes[0].getY());
	for (size_t i = 0; i < nodes.size(); i++)
	{
		prevAllCoor.insert(std::make_pair(nodes[i].getX(), nodes[i].getY()));
	}
}

// �ߣ��ƶ�
void GameScene::snakeMove() {
	auto prevTail = snake.getNodes().back();
	auto prevTailCoor = std::make_pair(prevTail.getX(), prevTail.getY());
	snake.move();
	prevAllCoor.erase(prevTailCoor);  // �ƶ���ֱ�����֮ǰ��β�����꣬�����ж�ͷ����û��ײ������
}

// ײ�����ж����ڸ�������֮ǰ�ж���
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

// ȷ��ͷ����ײ�������ֱ�Ӹ�����ͷռ������
void GameScene::updateHeadCoor() {
	auto currHead = snake.getNodes().front();
	prevHeadCoor = std::make_pair(currHead.getX(), currHead.getY());
	prevAllCoor.insert(prevHeadCoor);
}

// ײǽ�ж�
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

// ��ʳ���ж�
bool GameScene::isCollisionWithFood() {
	return prevHeadCoor.first == food.getX() && prevHeadCoor.second == food.getY();
}

// �Ե�ʳ��󣬸����߳��ȣ�����������ʳ��
void GameScene::afterEatFoods() {
	if (isCollisionWithFood()) {
		snake.grow();
		food.regenerate(prevAllCoor);
		m_score += 1;
		// ������Ч
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

// ʹ��˫�����ͼ��������
void GameScene::drawScreen() {
	BeginBatchDraw();
	cleardevice();
	// ���Ʊ���
	setfillcolor(WHITE);
	fillrectangle(0, 0, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1);
	setfillcolor(BLACK);
	fillrectangle(EDGE_WIDTH, EDGE_WIDTH, WINDOW_WIDTH - EDGE_WIDTH, WINDOW_HEIGHT - EDGE_WIDTH);
	snake.draw();
	food.draw();
	// ��ʾ��ǰ����
	TCHAR s[100];
	RECT r = { 0, 0, WINDOW_WIDTH - 1, EDGE_WIDTH - 1 };
	_stprintf_s(s, _T("��ǰ�÷֣�%d"), m_score);		// �߰汾 VC �Ƽ�ʹ�� _stprintf_s ����
	settextstyle(20, 0, _T("Consolas"));
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	drawtext(s, &r, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	EndBatchDraw();
}

// ��Ӧ��Ϣ
void GameScene::onKeyDownMsg(ExMessage& msg) {
	if (msg.message == WM_KEYDOWN) {  // ��Ӧ������Ϣ
		if (msg.vkcode == VK_UP || msg.vkcode == VK_DOWN || msg.vkcode == VK_LEFT || msg.vkcode == VK_RIGHT) {
			//std::cout << static_cast<int>(msg.vkcode) << std::endl;
			// ����peekmessage�ķ��������ʣ����ٰ��������·�����ٸı�
			// �����Ҫ������ͷ��һ�ڣ��ߡ����ӡ�����λ�����жϿ���ǰ���ķ���
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
