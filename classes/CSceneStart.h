#pragma once
#ifndef CSCENESTART_H
#define CSCENESTART_H
#include "cocos2d.h"
USING_NS_CC;
class CSceneStart :public Layer{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(CSceneStart);
};
#endif // !CSCENESTART_H
