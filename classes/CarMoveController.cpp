#include "CarMoveController.h"

bool CarMoveController::init()
{
	m_car = nullptr;
	Car_horizontal_speed = 5;

	this->scheduleUpdate();
	RegisterTouchListener();  
	return true;
}

void CarMoveController::MoveLeft()
{
	float  car_PosX= m_car->getPositionX();  //汽车的坐标X
	car_PosX -= Car_horizontal_speed;
	m_car->setPositionX(car_PosX);

}

void CarMoveController::MoveRight()
{
	float  car_PosX = m_car->getPositionX();  //汽车的坐标X
	car_PosX += Car_horizontal_speed;
	m_car->setPositionX(car_PosX);
}

void CarMoveController::bindCar(Car* car)
{
	this->m_car = car;
}

void CarMoveController::RegisterTouchListener()
{
	auto TouchListener = EventListenerTouchOneByOne::create(); 
	TouchListener->onTouchBegan = [&](Touch* touch, Event* event) { 
		Point curTouchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
		log("point(%f,%f)", curTouchPoint.x, curTouchPoint.y);  //test:173-596
		return true;
	};
	TouchListener->onTouchMoved = [&](Touch* touch, Event* event) {
		Point curTouchPoint = Director::getInstance()->convertToGL(touch->getLocationInView()); //获取Touch碰触的位置
		Point tarCarPoint = m_car->getCurCarPoint();  //获取汽车的位置


		Point visibleSize = Director::getInstance()->getVisibleSize();
		   
		if (tarCarPoint.x < visibleSize.x * 5 / 22 || tarCarPoint.x> visibleSize.x * 17 / 22) {  //
			if( !m_car->isExplosion())   //判定 汽车是否已经爆炸
			m_car->CarExplosion();
			
		}
		if (curTouchPoint.x > tarCarPoint.x) {  //控制汽车的移动
			MoveRight();
		}
		else {
			MoveLeft();
		}
		return true;
	};

	TouchListener->onTouchEnded = [&](Touch* touch, Event* event) {
		return true;
	};

	TouchListener->onTouchCancelled = [&](Touch* touch, Event* event) {
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(TouchListener, this);
}

