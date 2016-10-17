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
	this->setVisible(false); //��������Ϊ���ɼ�
	auto _emitter = ParticleExplosion::create();  // ��ըЧ�� ParticleTest Demo��
	_emitter->retain();  //��֤������ú� ��������;
	if (this->getParent()!= nullptr) { 
		this->getParent()->addChild(_emitter, 10);  //��Car�ĸ��ڵ��� ���
	}
	_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("stars.png")); //��������  
	_emitter->setAutoRemoveOnFinish(true);  //�Զ��Ƴ��� �����Ժ�;
	_emitter->setPosition(getCurCarPoint());  // �����������¹ʵ�λ�ñ�ը!
	_emitter->setOnExitCallback ([]{    //������ը  ����Ϸ����
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
	
		if (!isExplosion()) { //�ж����Ƿ��Ѿ���ը

			mstr->isHide();   //���ޱ�ը
			CarExplosion();    //���ı�ըЧ��
		}
	}
}

float Car::getCarSpeed()
{


	return car_Speed;
}


