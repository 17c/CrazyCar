#ifndef MONSTER_H
#define MONSTER_H
#include "CarEntity.h"
class Monster :public CarEntity {
public:
	virtual bool init();
	CREATE_FUNC(Monster);


	int getSpeed();   //获取怪物的速度
	void isHide();    // 让怪物隐身
	bool isCrash(Monster* _mstr); // 怪物之间是否发生了碰撞
	void MonsterExplosion(); 
private:
	int monster_speed;   //怪物的垂直速度
};
#endif // !MONSTER_H

