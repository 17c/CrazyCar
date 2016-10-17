#include "CSceneStart.h"
#include "gateScene.h"
Scene * CSceneStart::createScene()
{
	Scene* scene = Scene::create();
	auto * layer = CSceneStart::create();
	scene->addChild(layer);
	return scene;
}

bool CSceneStart::init()
{
	if (!Layer::init()) {
		return false;
	}
	
	auto VisibleSize = Director::getInstance()->getVisibleSize();
	auto label = Label::createWithBMFont("fonts/bitmapFontTest3.fnt","The Crazy Car"); //��Ϸ����
	label->setBMFontSize(35.0);
	label->setPosition(Point(VisibleSize.width/2,VisibleSize.height*6/7)); 
	this->addChild(label);
	
	MenuItemFont::setFontName("fonts/Marker Felt.ttf");
	auto item1_start = MenuItemFont::create("Start",[](Ref* sender) 
	{
		Director::getInstance()->replaceScene(gateScene::createScene());
	                      });  //menu_start
	
	auto color_action = TintBy::create(0.5f, 0, -255, -255); //���� ��ť�Ķ���
	auto color_back = color_action->reverse();
	auto seq = Sequence::create(color_action, color_back, nullptr);
	item1_start->runAction(RepeatForever::create(seq));
	
	auto item_introduction = MenuItemFont::create("Introduction", [](Ref* sender) {

	});  //��ť����

	auto item_exit = MenuItemFont::create("exit", [](Ref* sender) {
		Director::getInstance()->end();

	});  //��ť �˳�

	auto menu = Menu::create(item1_start, item_introduction , item_exit,nullptr);  //��ʼ���˵�
	menu->alignItemsVertically();


	auto s = Director::getInstance()->getWinSize();


	/*���������ʼMenu�Ķ���Ч��   ����cpp-tests �е� MenuTests*/
	int i = 0;
	for (const auto &child : menu->getChildren()) {
		auto dstPoint = child->getPosition();
		int offset = (int)(s.width / 2 + 50);
		if (i % 2 == 0)
			offset = -offset;

		child->setPosition(Vec2(dstPoint.x + offset, dstPoint.y));
		child->runAction(
			EaseElasticOut::create(MoveBy::create(2, Vec2(dstPoint.x - offset, 0)), 0.35f)
		);
		i++;
	}

	this->addChild(menu);
	menu->runAction(ScaleTo::create(1, 1));
	return true;
}
