#pragma once
#include "Sprite.h"
#include<vector>

// ��
class Snake : public Sprite
{
public:
	Snake();  // ǿ�ƺ��ι���
	Snake(int x, int y);

	void setDir(int dir);

	int getDir();

	std::vector<Sprite> getNodes();
	
	void draw() override;

	void move();

	void grow();

private:
	std::vector<Sprite> nodes;
	BYTE m_dir;  // ����
};



