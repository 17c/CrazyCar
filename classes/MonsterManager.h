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
	Point initMonsterPoint(bool _isApeared);   //随机产生怪物在地图中的位置
	Point changePositionToTilePosition(Point pos);  //把坐标转换为TilePositon

private:
	int _MonsterNumber;
	Vector<Monster*> _MonstersVec;
	void CreateMonsters();
	Car* _car;
};
#endif // !MONSTERMANAGER_H

