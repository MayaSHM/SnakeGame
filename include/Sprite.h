#pragma once
#include<easyx.h>
#include "hyperParams.h"

// 单个块 
class Sprite
{
public:
	Sprite();
	Sprite(int x, int y);

	virtual void draw();
	void moveBy(int dx, int dy);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);

	virtual ~Sprite();
protected:
	int m_x;
	int m_y;
	COLORREF m_color;  //  用于表示颜色的DWORD
};

