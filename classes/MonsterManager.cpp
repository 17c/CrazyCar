#include "MonsterManager.h"
#include "cocos2d.h"
USING_NS_CC;

bool MonsterManager::init()
{
	_car = nullptr;
	_MonsterNumber = 13;
	CreateMonsters();
	this->scheduleUpdate();
	return true;
}

void MonsterManager::update(float dt)
{
	for  (auto  _Monster : _MonstersVec)
	{
		float m_posY=_Monster->getPositionY();  //怪物在场景中的位置
		m_posY -=_Monster->getSpeed();         //怪物的移速
		_Monster->setPositionY(m_posY);
		if (m_posY <= 0) {
			_Monster->setPosition(initMonsterPoint(true));
		}
		if(_car!=nullptr)
		_car->isCrash(_Monster);   //汽车是否和怪物发生碰撞


		for (auto _otherMonster : _MonstersVec) {  //怪物之间是否发生了碰撞
			if (_Monster != _otherMonster) {
				if (_Monster->isCrash(_otherMonster)) {  //检查它是否碰撞了
					_Monster->setPosition(initMonsterPoint(true));
					_otherMonster->setPosition(initMonsterPoint(true));  //两个Monster都应该被重置位置
					_Monster->setVisible(true);
					_otherMonster->setVisible(true);
				}
			}
		}
	}
}

void MonsterManager::bindCar(Car * car)
{
	this->_car = car;

}


Point MonsterManager::initMonsterPoint(bool _isApeared)
{
	struct timeval now;
	gettimeofday(&now, NULL);   // 计算时间种子  
   //初始化随机种子
	//timeval是个结构体，里边有俩个变量，一个是以秒为单位的，一个是以微秒为单位的 
	unsigned rand_seed = (unsigned)(now.tv_sec * 10000 + now.tv_usec / 10);     // 初始化随机数   
	srand(rand_seed);

	Point visibleSize = Director::getInstance()->getVisibleSize();
	float x = rand()%(static_cast<int>(visibleSize.x));
	while (true) // 假如在两个区间之外,则重新 随机产生数
	{
		if (x > visibleSize.x * 6 / 22 && x<visibleSize.x * 18 / 22) {
			break;
		}
		else {
			x = rand() % (static_cast<int>(visibleSize.x));
		}

	}
		
	float  y;
	if (!_isApeared) {
		 y = rand() % (static_cast<int>( visibleSize.y)) + 100; //随机产生坐标 y

	}
	else {
		 y = rand() % (static_cast<int>( visibleSize.y)) + visibleSize.y;
	}


	Point _tileMonsterPoint = this->changePositionToTilePosition(Point(x, y));

	int monster_x = _tileMonsterPoint.x * 70;  // 模板化 格子的坐标x
	int monster_y = visibleSize.y - _tileMonsterPoint.y * 70;   // 模板化 格子的坐标y
	//log("%d,%d", monster_x, monster_y);
	
	return Point(monster_x, monster_y);
}

Point MonsterManager::changePositionToTilePosition(Point pos)   //这个函数在这个游戏里其实用不上 .因为我的决定不按照格子来
{
	//auto _mapSize = this->_TmxMap->getMapSize();  

	auto visibleSize = Director::getInstance()->getVisibleSize();
	int Pos_x = pos.x / 70.0;
	int Pos_y = (visibleSize.height- pos.y) / 70.0;  //  TileMap 用的不是GL坐标
	
	return Point(Pos_x, Pos_y);
}

void MonsterManager::CreateMonsters()
{
	SpriteFrameCache* sfc = SpriteFrameCache::getInstance();  //创建一个精灵面板缓冲池

	sfc->addSpriteFramesWithFile("Monsters.plist", "Monsters.png");  //把这个集合加入集合中

	for (int i = 0; i < _MonsterNumber; i++) {       // 创建精灵个数
		
		int _MonsterType = static_cast<int>(rand()%10+1);  // 怪兽的种类
	
		String _MonsterName = "car" + std::to_string(_MonsterType) + ".png"; //怪兽名
		log("%s", _MonsterName);  //检验值
		auto monster = Monster::create();
		Sprite* _mstr = Sprite::createWithSpriteFrameName(_MonsterName.getCString());//创建CarSprite
		monster->bindSprite(_mstr); //将精灵与怪兽绑定

		//**出错位置
		monster->setPosition(initMonsterPoint(false));


		_MonstersVec.pushBack(monster);    //保存在Vector中
		
		this->addChild(monster);
		
	}


}
