#include "CarEntity.h"
#pragma once

void CarEntity::bindSprite(Sprite * sprite)
{
	this->m_Sprite = sprite;
	this->addChild(m_Sprite);

	auto sprt_Size = m_Sprite->getContentSize();  //获取精灵的内容尺寸
	this->setContentSize(sprt_Size); 
	m_Sprite->setPosition(Point(sprt_Size.width/2, sprt_Size.height/2));   // 与锚点有关,我的默认锚点是0.5 因此 是/2
}
