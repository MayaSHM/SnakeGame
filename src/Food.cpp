#include "../include/Food.h"

Food::Food() {
	m_x = SNAKE_WIDTH * 5 + EDGE_WIDTH;
	m_y = SNAKE_WIDTH * 5 + EDGE_WIDTH;
	m_color = BLUE;
}

Food::Food(std::unordered_set<std::pair<int, int>, pairHash>& SnakeBodyCoor) {
	Food::regenerate(SnakeBodyCoor);
}

void Food::draw() {
	setfillcolor(m_color);
	fillrectangle(m_x, m_y, m_x + SNAKE_WIDTH, m_y + SNAKE_WIDTH);
}

void Food::regenerate(std::unordered_set<std::pair<int, int>, pairHash>& SnakeBodyCoor) {
	// 不要在蛇身上生成食物
	int nextX = rand() % ((WINDOW_WIDTH - 2 * EDGE_WIDTH) / SNAKE_WIDTH) * SNAKE_WIDTH + EDGE_WIDTH;
	int nextY = rand() % ((WINDOW_HEIGHT - 2 * EDGE_WIDTH) / SNAKE_WIDTH) * SNAKE_WIDTH + EDGE_WIDTH;
	std::pair<int, int> nextCoor = std::make_pair(nextX, nextY);
	while (SnakeBodyCoor.count(nextCoor) > 0) {
		nextX = rand() % ((WINDOW_WIDTH - 2 * EDGE_WIDTH) / SNAKE_WIDTH) * SNAKE_WIDTH + EDGE_WIDTH;
		nextY = rand() % ((WINDOW_HEIGHT - 2 * EDGE_WIDTH) / SNAKE_WIDTH) * SNAKE_WIDTH + EDGE_WIDTH;
		std::pair<int, int> nextCoor = std::make_pair(nextX, nextY);
	}
	m_x = nextX;
	m_y = nextY;
	m_color = BLUE;
}
