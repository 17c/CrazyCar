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
	TMXTiledMap* m_backGround_1;  //������ͼ1
	TMXTiledMap* m_backGround_2;   // ������ͼ2
	Car* m_car;     //���



	// UI��ʵ���Ӧ���Լ�ȥ����дһ����,����UI �Ƚϼ� ��ֱ�Ӻϲ���
	bool isPause; //��ť��ͣ�Ŀ���
	ui::Button* bt_pause;  //��ͣ

	ui::TextField* tf_score;  //�Ƿ���
	float score;

	ui::Button* bt_turnBack; // ��Ŀ¼
};
#endif // !GATESCENE_H
