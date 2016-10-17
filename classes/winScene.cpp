#include "winScene.h"

Scene * winScene::createScene()
{
	auto scene = Scene::create();
	auto layer = winScene::create();
	scene->addChild(layer);
	return scene;
}

bool winScene::init()
{
	if (!Layer::init()) {
		return false;
	}
	auto VisibleSize = Director::getInstance()->getVisibleSize();
	Label* lb = Label::create("game,over","Arial",24);
	lb->setPosition(Point(VisibleSize.width / 2, VisibleSize.height/2));
	this->addChild(lb);
	return true;
}
