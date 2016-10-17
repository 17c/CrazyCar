#include "Monster.h"

bool Monster::init()
{
	struct timeval now;
	gettimeofday(&now, NULL);   // ����ʱ������  
								//��ʼ���������
								//timeval�Ǹ��ṹ�壬���������������һ��������Ϊ��λ�ģ�һ������΢��Ϊ��λ�� 
	unsigned rand_seed = (unsigned)(now.tv_sec * 10000 + now.tv_usec / 10);     // ��ʼ�������   
	srand(rand_seed);

	monster_speed = rand() % 2+2;  //����Ϊ��� 2-4
	
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
	this->setVisible(false); //���ù���Ϊ���ɼ�
	auto _emitter = ParticleExplosion::create();  // ��ըЧ�� ParticleTest Demo��
	_emitter->retain();  //��֤������ú� ��������;
	if (this->getParent() != nullptr) {
		this->getParent()->addChild(_emitter, 10);  //��Car�ĸ��ڵ��� ���
	}
	_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("stars.png")); //��������  
	_emitter->setAutoRemoveOnFinish(true);  //�Զ��Ƴ��� �����Ժ�;
	_emitter->setPosition(this->getPosition());  // �����������¹ʵ�λ�ñ�ը!
}




