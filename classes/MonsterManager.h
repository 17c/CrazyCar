#ifndef MONSTERMANAGER_H
#define MONSTERMANAGER_H
#include "cocos2d.h"
#include  "Monster.h"
#include "Car.h"
USING_NS_CC;
class MonsterManager :public Node {
public:
	virtual bool init();
	CREATE_FUNC(MonsterManager);
	
	virtual void update(float dt);
	void bindCar(Car* car);



	void setMonsterNum(int _mstrnbr);
	Point initMonsterPoint(bool _isApeared);   //������������ڵ�ͼ�е�λ��
	Point changePositionToTilePosition(Point pos);  //������ת��ΪTilePositon

private:
	int _MonsterNumber;
	Vector<Monster*> _MonstersVec;
	void CreateMonsters();
	Car* _car;
};
#endif // !MONSTERMANAGER_H

