#include "../include/Sprite.h"

Sprite::Sprite(): Sprite::Sprite(0, 0) {};

Sprite::Sprite(int x, int y) : m_x(x), m_y(y), m_color(RED) {};  // 初始化参数列表

void Sprite::draw() {
	setfillcolor(m_color);
	fillrectangle(m_x, m_y, m_x + SNAKE_WIDTH, m_y + SNAKE_WIDTH);
}

// 移动一定距离
void Sprite::moveBy(int dx, int dy) {  
	m_x += dx;
	m_y += dy;
}

int Sprite::getX() {
	return m_x;
}

int Sprite::getY() {
	return m_y;
}

void Sprite::setX(int x) {
	m_x = x;
}

void Sprite::setY(int y) {
	m_y = y;
}

Sprite::~Sprite() {

}
