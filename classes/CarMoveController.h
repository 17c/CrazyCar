#pragma once
#include "Car.h"
class CarMoveController: public Node {
public:
	virtual bool init();
	CREATE_FUNC(CarMoveController);

	void MoveLeft();   //�����ƶ�
	void MoveRight();  //�����ƶ�
	void bindCar(Car* car);  //��Car��;
	void RegisterTouchListener();//ע��Touch������
private:
	Car* m_car;
	float Car_horizontal_speed;  //����ˮƽ�ƶ��ľ���
};