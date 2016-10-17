#pragma once
#ifndef CSCENELOSE_H
#include "cocos2d.h"
USING_NS_CC;
class CSceneLose :public Layer {
public:

	static Scene* creatScene();
	virtual bool init();

	CREATE_FUNC(CSceneLose);
};
#endif // !CSCENELOSE_H
