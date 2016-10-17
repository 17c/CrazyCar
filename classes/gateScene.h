#pragma once
#ifndef GATESCENE_H
#define GATESCENE_H
#include"cocos2d.h"
#include  "Car.h"
#include "ui\CocosGUI.h"
#include "cocostudio\CocoStudio.h"
using namespace cocos2d;
class gateScene : public Layer {
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(gateScene);
	virtual void update(float dt);
	void LoadUI();
private:
	TMXTiledMap* m_backGround_1;  //场景地图1
	TMXTiledMap* m_backGround_2;   // 场景地图2
	Car* m_car;     //玩家



	// UI其实最好应该自己去单独写一个类,但是UI 比较简单 就直接合并了
	bool isPause; //按钮暂停的控制
	ui::Button* bt_pause;  //暂停

	ui::TextField* tf_score;  //记分器
	float score;

	ui::Button* bt_turnBack; // 回目录
};
#endif // !GATESCENE_H
