#pragma once
#include "Sprite.h"
#include<vector>

// 蛇
class Snake : public Sprite
{
public:
	Snake();  // 强制含参构造
	Snake(int x, int y);

	void setDir(int dir);

	int getDir();

	std::vector<Sprite> getNodes();
	
	void draw() override;

	void move();

	void grow();

private:
	std::vector<Sprite> nodes;
	BYTE m_dir;  // 方向
};



