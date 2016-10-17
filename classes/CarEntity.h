#pragma once
#include"cocos2d.h"
using namespace cocos2d;
class CarEntity :public Node {
public:
	void bindSprite(Sprite* sprite);
private:
	Sprite* m_Sprite;
};