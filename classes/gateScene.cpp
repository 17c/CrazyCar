#include "gateScene.h"
#include "Car.h"
#include "CarMoveController.h"
#include "MonsterManager.h"
#include "CSceneStart.h"
#include "cocos2d.h"
USING_NS_CC;
Scene * gateScene::createScene()
{
	auto scene = Scene::create();
	auto Layer = gateScene::create();
	scene->addChild(Layer);
	return scene;
}

bool gateScene::init()
{
	if (!Layer::init()) {
		return false;
	}
	score = 0.0; //������Ϊ0
	isPause = false;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->scheduleUpdate();
	auto CarMap_1 = TMXTiledMap::create("CarMap.tmx");   //��ʼ��������ͼ1;
	m_backGround_1 = CarMap_1;   //��ʼ�� s_CarMap��ֵ
	log("X:%f,Y:%f", CarMap_1->getContentSize().width, CarMap_1->getContentSize().height);
	log("PosX:%f,PosY: %f", CarMap_1->getPositionX(),CarMap_1->getPositionY());//X:770.000000,Y:4200.000000  PosY: 0.000000

	auto CarMap_2 = TMXTiledMap::create("CarMap.tmx");  //��ʼ�� ������ͼ2
	m_backGround_2 = CarMap_2;
	CarMap_2->setPositionY(CarMap_1->getPositionY()+CarMap_1->getContentSize().height);   //���õ�ͼ2������

	this->addChild(CarMap_1,0);
	this->addChild(CarMap_2,0);
	
	auto car = Car::create(); //����Player;
	Sprite*  s_car = Sprite::create("Car.png");  // ����һ������s_car
	car->bindSprite(s_car);//��Player��
	//car->bindMap(CarMap); //��CarMap��������
	this->addChild(car);//���볡����
	m_car = car;

	TMXObjectGroup* player = CarMap_1->getObjectGroup("player"); //��ȡͼ�β�
	auto playerPointMap = player->getObject("playerPoint"); // ��ȡͼ�β��һ������PlayerPoint
	float PlayerPosX = playerPointMap.at("x").asFloat(); //��ȡ��������Xֵ
	float PlayerPosY = playerPointMap.at("y").asFloat(); //��ȡ��������Yֵ
	car->setPosition(Point(PlayerPosX, PlayerPosY));//�������������λ��



	auto carController = CarMoveController::create();  //���� �����ƶ�������
	carController->bindCar(car);  //������������
	car->addChild(carController);  //Ϊ�˷�ֹ�����ƶ���������release()��
	

	MonsterManager* monsterManager = MonsterManager::create();   //��ʼ�����������
	monsterManager->bindCar(car);  // ���޹�������������
	this->addChild(monsterManager);


	LoadUI();  //����UI
	return true;
}

void gateScene::update(float dt)
{
	score = score + dt;
	float fbackGround_1_PosY = m_backGround_1->getPositionY();  
	fbackGround_1_PosY -= m_car->getCarSpeed();
	m_backGround_1->setPositionY(fbackGround_1_PosY);  //�õ�ͼ1 �Լ�������
	log("%f", fbackGround_1_PosY);
	
	float fbackGround_2_PosY = m_backGround_2->getPositionY();
	fbackGround_2_PosY -= m_car->getCarSpeed();
	m_backGround_2->setPositionY(fbackGround_2_PosY);  //�õ�ͼ2 �Լ�������
	
	
	if (fbackGround_1_PosY <= -(m_backGround_1->getContentSize().height)) {   //����ͼ1������С�ڵ��� -height/2 ʱ  ������������Ϊ 
		m_backGround_1->setPositionY(m_backGround_1->getContentSize().height);
	}
	
	if (fbackGround_2_PosY <= -(m_backGround_2->getContentSize().height)) {   //����ͼ2������С�ڵ��� -height/2 ʱ  ������������Ϊ 
		m_backGround_2->setPositionY(m_backGround_2->getContentSize().height);
	}

	tf_score->setText(Value(score).asString());
}

void gateScene::LoadUI()
{
	auto ui  = CSLoader::createNode("scene1.csb");
	this->addChild(ui,0);
	 bt_pause =static_cast<ui::Button*>(ui->getChildByName("bt_pause"));  //��ȡ��ͣ��ť
	 bt_pause->addClickEventListener([=](Ref* sender) {
		 
			 if (!isPause) {
				 Director::getInstance()->pause();
				 isPause = true;
			 }
			 else {
				 Director::getInstance()->resume();
				 isPause = false;
			 }

		 
	 });
	 bt_turnBack = static_cast<ui::Button*>(ui->getChildByName("bt_back"));  //����Ŀ¼
	 bt_turnBack->addClickEventListener([](Ref* sender) {
		 Director::getInstance()->replaceScene(CSceneStart::createScene());
	 });

	 tf_score = static_cast<ui::TextField*>(ui->getChildByName("tf_score")); //��ȡ �Ƿ����
}

