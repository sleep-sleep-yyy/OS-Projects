#include "all_in_out.h"

all_in_out::all_in_out(QWidget* parent)
	: QMainWindow(parent)
{

	//ui.setupUi(this);
	for (int i = 0; i < ELEVATOR_NUM; i++)
	{
		Os1* elevator = new Os1(nullptr, i, FLOOR_NUM);
		elevator->move(5 + i % (GetSystemMetrics(SM_CXSCREEN) / elevator->width()) * (elevator->width() +2),10);//5 + ((i + 1) * elevator->width() / GetSystemMetrics(SM_CXSCREEN)) * (elevator->height() + 35)
		elevator->show();
		elevators.push_back(elevator);
	}
	outside* to_choose = new outside(nullptr, elevators, FLOOR_NUM);//初始化一个拥有ELEVATOR_NUM个电梯的大楼
	to_choose->move((GetSystemMetrics(SM_CXSCREEN) - to_choose->width())/2-200,450);
	to_choose->show();
}
all_in_out::~all_in_out()
{}
