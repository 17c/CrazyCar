#pragma once
#include "CarEntity.h"
#include "Monster.h"
class Car: public CarEntity {
public:
    virtual bool init();  //��ʼ������
    CREATE_FUNC(Car);
 
    virtual void update(float dt);
	 void addCarSpeed();            //���ӳ���
	 Point getCurCarPoint();
	 void CarExplosion();   //������ײ�ı�ըЧ��
	 bool isExplosion();    //�ж������Ƿ��Ѿ���ը
	 void isCrash(Monster* mstr);          //�ж������Ƿ�ײ��
	 float getCarSpeed();   //��ȡ �������ٶ�
private:
	float car_Speed;    //������
	bool car_is_Explosion;
};