#pragma once
#include "Car.h"
class CarMoveController: public Node {
public:
	virtual bool init();
	CREATE_FUNC(CarMoveController);

	void MoveLeft();   //向左移动
	void MoveRight();  //向右移动
	void bindCar(Car* car);  //和Car绑定;
	void RegisterTouchListener();//注册Touch监听器
private:
	Car* m_car;
	float Car_horizontal_speed;  //汽车水平移动的距离
};