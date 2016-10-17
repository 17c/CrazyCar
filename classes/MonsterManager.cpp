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
		float m_posY=_Monster->getPositionY();  //�����ڳ����е�λ��
		m_posY -=_Monster->getSpeed();         //���������
		_Monster->setPositionY(m_posY);
		if (m_posY <= 0) {
			_Monster->setPosition(initMonsterPoint(true));
		}
		if(_car!=nullptr)
		_car->isCrash(_Monster);   //�����Ƿ�͹��﷢����ײ


		for (auto _otherMonster : _MonstersVec) {  //����֮���Ƿ�������ײ
			if (_Monster != _otherMonster) {
				if (_Monster->isCrash(_otherMonster)) {  //������Ƿ���ײ��
					_Monster->setPosition(initMonsterPoint(true));
					_otherMonster->setPosition(initMonsterPoint(true));  //����Monster��Ӧ�ñ�����λ��
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
	gettimeofday(&now, NULL);   // ����ʱ������  
   //��ʼ���������
	//timeval�Ǹ��ṹ�壬���������������һ��������Ϊ��λ�ģ�һ������΢��Ϊ��λ�� 
	unsigned rand_seed = (unsigned)(now.tv_sec * 10000 + now.tv_usec / 10);     // ��ʼ�������   
	srand(rand_seed);

	Point visibleSize = Director::getInstance()->getVisibleSize();
	float x = rand()%(static_cast<int>(visibleSize.x));
	while (true) // ��������������֮��,������ ���������
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
		 y = rand() % (static_cast<int>( visibleSize.y)) + 100; //����������� y

	}
	else {
		 y = rand() % (static_cast<int>( visibleSize.y)) + visibleSize.y;
	}


	Point _tileMonsterPoint = this->changePositionToTilePosition(Point(x, y));

	int monster_x = _tileMonsterPoint.x * 70;  // ģ�廯 ���ӵ�����x
	int monster_y = visibleSize.y - _tileMonsterPoint.y * 70;   // ģ�廯 ���ӵ�����y
	//log("%d,%d", monster_x, monster_y);
	
	return Point(monster_x, monster_y);
}

Point MonsterManager::changePositionToTilePosition(Point pos)   //��������������Ϸ����ʵ�ò��� .��Ϊ�ҵľ��������ո�����
{
	//auto _mapSize = this->_TmxMap->getMapSize();  

	auto visibleSize = Director::getInstance()->getVisibleSize();
	int Pos_x = pos.x / 70.0;
	int Pos_y = (visibleSize.height- pos.y) / 70.0;  //  TileMap �õĲ���GL����
	
	return Point(Pos_x, Pos_y);
}

void MonsterManager::CreateMonsters()
{
	SpriteFrameCache* sfc = SpriteFrameCache::getInstance();  //����һ��������建���

	sfc->addSpriteFramesWithFile("Monsters.plist", "Monsters.png");  //��������ϼ��뼯����

	for (int i = 0; i < _MonsterNumber; i++) {       // �����������
		
		int _MonsterType = static_cast<int>(rand()%10+1);  // ���޵�����
	
		String _MonsterName = "car" + std::to_string(_MonsterType) + ".png"; //������
		log("%s", _MonsterName);  //����ֵ
		auto monster = Monster::create();
		Sprite* _mstr = Sprite::createWithSpriteFrameName(_MonsterName.getCString());//����CarSprite
		monster->bindSprite(_mstr); //����������ް�

		//**����λ��
		monster->setPosition(initMonsterPoint(false));


		_MonstersVec.pushBack(monster);    //������Vector��
		
		this->addChild(monster);
		
	}


}
