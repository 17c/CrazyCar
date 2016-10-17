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
	score = 0.0; //分数记为0
	isPause = false;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->scheduleUpdate();
	auto CarMap_1 = TMXTiledMap::create("CarMap.tmx");   //初始化赛车地图1;
	m_backGround_1 = CarMap_1;   //初始化 s_CarMap的值
	log("X:%f,Y:%f", CarMap_1->getContentSize().width, CarMap_1->getContentSize().height);
	log("PosX:%f,PosY: %f", CarMap_1->getPositionX(),CarMap_1->getPositionY());//X:770.000000,Y:4200.000000  PosY: 0.000000

	auto CarMap_2 = TMXTiledMap::create("CarMap.tmx");  //初始化 赛车地图2
	m_backGround_2 = CarMap_2;
	CarMap_2->setPositionY(CarMap_1->getPositionY()+CarMap_1->getContentSize().height);   //设置地图2的坐标

	this->addChild(CarMap_1,0);
	this->addChild(CarMap_2,0);
	
	auto car = Car::create(); //创建Player;
	Sprite*  s_car = Sprite::create("Car.png");  // 创建一个精灵s_car
	car->bindSprite(s_car);//与Player绑定
	//car->bindMap(CarMap); //将CarMap与汽车绑定
	this->addChild(car);//加入场景中
	m_car = car;

	TMXObjectGroup* player = CarMap_1->getObjectGroup("player"); //获取图形层
	auto playerPointMap = player->getObject("playerPoint"); // 获取图形层的一个属性PlayerPoint
	float PlayerPosX = playerPointMap.at("x").asFloat(); //获取玩家坐标的X值
	float PlayerPosY = playerPointMap.at("y").asFloat(); //获取玩家坐标的Y值
	car->setPosition(Point(PlayerPosX, PlayerPosY));//设置玩家汽车的位置



	auto carController = CarMoveController::create();  //创建 汽车移动控制器
	carController->bindCar(car);  //将其与汽车绑定
	car->addChild(carController);  //为了防止汽车移动控制器被release()掉
	

	MonsterManager* monsterManager = MonsterManager::create();   //初始化怪物管理器
	monsterManager->bindCar(car);  // 怪兽管理器与汽车绑定
	this->addChild(monsterManager);


	LoadUI();  //加载UI
	return true;
}

void gateScene::update(float dt)
{
	score = score + dt;
	float fbackGround_1_PosY = m_backGround_1->getPositionY();  
	fbackGround_1_PosY -= m_car->getCarSpeed();
	m_backGround_1->setPositionY(fbackGround_1_PosY);  //让地图1 自己动起来
	log("%f", fbackGround_1_PosY);
	
	float fbackGround_2_PosY = m_backGround_2->getPositionY();
	fbackGround_2_PosY -= m_car->getCarSpeed();
	m_backGround_2->setPositionY(fbackGround_2_PosY);  //让地图2 自己动起来
	
	
	if (fbackGround_1_PosY <= -(m_backGround_1->getContentSize().height)) {   //当地图1的坐标小于等于 -height/2 时  设置它的坐标为 
		m_backGround_1->setPositionY(m_backGround_1->getContentSize().height);
	}
	
	if (fbackGround_2_PosY <= -(m_backGround_2->getContentSize().height)) {   //当地图2的坐标小于等于 -height/2 时  设置它的坐标为 
		m_backGround_2->setPositionY(m_backGround_2->getContentSize().height);
	}

	tf_score->setText(Value(score).asString());
}

void gateScene::LoadUI()
{
	auto ui  = CSLoader::createNode("scene1.csb");
	this->addChild(ui,0);
	 bt_pause =static_cast<ui::Button*>(ui->getChildByName("bt_pause"));  //读取暂停按钮
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
	 bt_turnBack = static_cast<ui::Button*>(ui->getChildByName("bt_back"));  //返回目录
	 bt_turnBack->addClickEventListener([](Ref* sender) {
		 Director::getInstance()->replaceScene(CSceneStart::createScene());
	 });

	 tf_score = static_cast<ui::TextField*>(ui->getChildByName("tf_score")); //读取 记分面板
}

