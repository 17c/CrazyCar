#include "CSceneLose.h"

Scene * CSceneLose::creatScene()
{
	Scene*  scene = Scene::create();
	auto layer = CSceneLose::create();
	scene->addChild(layer);
	return scene;
}

bool CSceneLose::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto VisibleSize = Director::getInstance()->getVisibleSize();
	auto loseLogo = Sprite::create("lose.png");
	loseLogo->setPosition(Point(VisibleSize.width/2, VisibleSize.height/2));
	this->addChild(loseLogo);
	return true;
}
