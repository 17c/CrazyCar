#include "Car.h"
#include "CSceneLose.h"
bool Car::init()
{
	
	car_Speed = 1;
	car_is_Explosion = false;
	this->scheduleUpdate();

	return true;

}


void Car::update(float dt)
{

	
}

void Car::addCarSpeed()
{
	++car_Speed;;
}

Point Car::getCurCarPoint()
{
	Point car_vec2=(Point)this->getPosition();
	return car_vec2;
}

void Car::CarExplosion()
{
	this->setVisible(false); //设置汽车为不可见
	auto _emitter = ParticleExplosion::create();  // 爆炸效果 ParticleTest Demo中
	_emitter->retain();  //保证这个调用后 不被销毁;
	if (this->getParent()!= nullptr) { 
		this->getParent()->addChild(_emitter, 10);  //在Car的父节点里 添加
	}
	_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("stars.png")); //新增纹理  
	_emitter->setAutoRemoveOnFinish(true);  //自动移除在 结束以后;
	_emitter->setPosition(getCurCarPoint());  // 在汽车发生事故的位置爆炸!
	_emitter->setOnExitCallback ([]{    //汽车爆炸  则游戏结束
		Director::getInstance()->replaceScene(CSceneLose::creatScene());
	});

	car_is_Explosion = true;   
}

bool Car::isExplosion()
{
	return car_is_Explosion;
}

void Car::isCrash(Monster* mstr)
{
	if (this->boundingBox().intersectsRect(mstr->boundingBox())) {
	
		if (!isExplosion()) { //判定车是否已经爆炸

			mstr->isHide();   //怪兽爆炸
			CarExplosion();    //车的爆炸效果
		}
	}
}

float Car::getCarSpeed()
{


	return car_Speed;
}


