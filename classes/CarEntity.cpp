#include "CarEntity.h"
#pragma once

void CarEntity::bindSprite(Sprite * sprite)
{
	this->m_Sprite = sprite;
	this->addChild(m_Sprite);

	auto sprt_Size = m_Sprite->getContentSize();  //��ȡ��������ݳߴ�
	this->setContentSize(sprt_Size); 
	m_Sprite->setPosition(Point(sprt_Size.width/2, sprt_Size.height/2));   // ��ê���й�,�ҵ�Ĭ��ê����0.5 ��� ��/2
}
