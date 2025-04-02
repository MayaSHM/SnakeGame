#pragma once
#include "../include/Sprite.h"
#include<utility>
#include<vector>
#include<unordered_set>
#include "pairHash.h"

// Ê³Îï
class Food : public Sprite {
public:
	Food();
	Food(std::unordered_set<std::pair<int, int>, pairHash>& SnakeBodyCoor);

	void draw() override;

	void regenerate(std::unordered_set<std::pair<int, int>, pairHash>& SnakeBodyCoor);
private:

};
