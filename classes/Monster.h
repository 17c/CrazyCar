#ifndef MONSTER_H
#define MONSTER_H
#include "CarEntity.h"
class Monster :public CarEntity {
public:
	virtual bool init();
	CREATE_FUNC(Monster);


	int getSpeed();   //��ȡ������ٶ�
	void isHide();    // �ù�������
	bool isCrash(Monster* _mstr); // ����֮���Ƿ�������ײ
	void MonsterExplosion(); 
private:
	int monster_speed;   //����Ĵ�ֱ�ٶ�
};
#endif // !MONSTER_H

