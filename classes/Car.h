#pragma once
#include "CarEntity.h"
#include "Monster.h"
class Car: public CarEntity {
public:
    virtual bool init();  //初始化对象
    CREATE_FUNC(Car);
 
    virtual void update(float dt);
	 void addCarSpeed();            //增加车速
	 Point getCurCarPoint();
	 void CarExplosion();   //汽车碰撞的爆炸效果
	 bool isExplosion();    //判断汽车是否已经爆炸
	 void isCrash(Monster* mstr);          //判断汽车是否撞车
	 float getCarSpeed();   //获取 汽车的速度
private:
	float car_Speed;    //车移速
	bool car_is_Explosion;
};