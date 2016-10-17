#include "Monster.h"

bool Monster::init()
{
	struct timeval now;
	gettimeofday(&now, NULL);   // 计算时间种子  
								//初始化随机种子
								//timeval是个结构体，里边有俩个变量，一个是以秒为单位的，一个是以微妙为单位的 
	unsigned rand_seed = (unsigned)(now.tv_sec * 10000 + now.tv_usec / 10);     // 初始化随机数   
	srand(rand_seed);

	monster_speed = rand() % 2+2;  //车速为随机 2-4
	
	return true;
}

int Monster::getSpeed()
{
	return monster_speed;
}

void Monster::isHide()
{
	this->setVisible(false);
}

bool Monster::isCrash(Monster* _mstr)
{
	if (this->getBoundingBox().intersectsRect(_mstr->getBoundingBox())) {
		MonsterExplosion();
		_mstr->isHide();
		return true;
	}
	return false;
}

void Monster::MonsterExplosion()
{
	this->setVisible(false); //设置怪物为不可见
	auto _emitter = ParticleExplosion::create();  // 爆炸效果 ParticleTest Demo中
	_emitter->retain();  //保证这个调用后 不被销毁;
	if (this->getParent() != nullptr) {
		this->getParent()->addChild(_emitter, 10);  //在Car的父节点里 添加
	}
	_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("stars.png")); //新增纹理  
	_emitter->setAutoRemoveOnFinish(true);  //自动移除在 结束以后;
	_emitter->setPosition(this->getPosition());  // 在汽车发生事故的位置爆炸!
}




