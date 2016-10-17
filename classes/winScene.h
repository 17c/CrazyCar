#pragma once
#ifndef WINSCENE_H
#define WINSCENE_H
#include "cocos2d.h"
using namespace cocos2d;
class winScene :public Layer {
public :
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(winScene);

};
#endif // !WINSCENE_H
