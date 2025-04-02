#include"../include/Snake.h"

Snake::Snake() : Snake::Snake(0, 0) {};  // ǿ�ƺ��ι���

Snake::Snake(int x, int y) : Sprite(x, y), m_dir(VK_RIGHT) {
	nodes.push_back(Sprite(x + 3 * SNAKE_WIDTH, y + 1 * SNAKE_WIDTH));
	nodes.push_back(Sprite(x + 2 * SNAKE_WIDTH, y + 1 * SNAKE_WIDTH));
	nodes.push_back(Sprite(x + 1 * SNAKE_WIDTH, y + 1 * SNAKE_WIDTH));  // β��ջ��
}

void Snake::setDir(int dir) {
	m_dir = dir;
}

int Snake::getDir() {
	return m_dir;
}

std::vector<Sprite> Snake::getNodes() {
	return nodes;
}

void Snake::draw() {
	for (auto& node : nodes) {
		node.draw();  // ��������ÿһ��
	}
}

void Snake::move() {
	// ���������ͷ�����ȸ��������ٸ�����ͷ��
	for (size_t i = nodes.size() - 1; i > 0; i--)
	{
		nodes[i] = nodes[i - 1];
	}
	// ��ͷ�ƶ�
	if (m_dir == VK_UP) {
		nodes[0].moveBy(0, -SNAKE_WIDTH);
	}
	else if (m_dir == VK_DOWN) {
		nodes[0].moveBy(0, SNAKE_WIDTH);
	}
	else if (m_dir == VK_LEFT) {
		nodes[0].moveBy(-SNAKE_WIDTH, 0);
	}
	else if (m_dir == VK_RIGHT) {
		nodes[0].moveBy(SNAKE_WIDTH, 0);
	}
}

void Snake::grow() {
	nodes.push_back(Sprite(-SNAKE_WIDTH, -SNAKE_WIDTH));  // �ڿ�������λ������һ������
}

