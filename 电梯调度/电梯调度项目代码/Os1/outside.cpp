#include "outside.h"

outside::outside(QWidget* parent, vector<Os1*> Elevators, int floor_num): QWidget(parent)
{
	ui.setupUi(this);
	elevators = Elevators;//在此对elevators进行赋值，此时内部已经有5个电梯了
	//draw btns
	for (int i = 0; i < floor_num; i++) {
		QLabel* floorNo = new QLabel(ui.groupBox);
		floorNo->setGeometry(20 + 40 * (i % 10), 30 + 120 * (i / 10), 30, 30);
		floorNo->setAlignment(Qt::AlignHCenter);
		floorNo->setText(QString::number(i + 1, 10));
		floorNo->show();
		QPushButton* floorBtnUp = new QPushButton(ui.groupBox);
		floorBtnUp->setGeometry(20 + 40 * (i % 10), 60 + 120 * (i / 10), 30, 30);
		floorBtnUp->setText("UP");
		floorBtnUp->show();
		floorBtnsUp.push_back(floorBtnUp);
		connect(floorBtnsUp[unsigned(i)], &QPushButton::clicked, [=] {
			floorBtnsUp[unsigned(i)]->setEnabled(false);
			floorBtnsUp[unsigned(i)]->setStyleSheet("background-color: rgb(84, 255, 159);");
			select_outside(UP, i); });
		QPushButton* floorBtnDown = new QPushButton(ui.groupBox);
		floorBtnDown->setGeometry(20 + 40 * (i % 10), 100 + 120 * (i / 10), 30, 30);
		floorBtnDown->setText("DN");
		floorBtnDown->show();
		floorBtnsDown.push_back(floorBtnDown);
		connect(floorBtnsDown[unsigned(i)], &QPushButton::clicked, [=] {
			floorBtnsDown[unsigned(i)]->setEnabled(false);
			floorBtnsDown[unsigned(i)]->setStyleSheet("background-color: rgb(84, 255, 159);");
			select_outside(DOWN, i); });
	}
	QTimer* timer2 = new QTimer(this);
	connect(timer2, &QTimer::timeout, this,&outside::refresh);
	timer2->start(500);
}
//经过对所有情况的讨论，总结出只有在（1）电梯空闲（2）电梯运行且人请求方向与电梯运行方向一致且人在电梯运行方向上 时，距离才为/user_floor-ele_floor/
//其余情况皆为/last_task_floor-user_floor/+/last_task_floor+ele_floor/
//由此计算优先度
int outside::priority_cal(int user_choice, int user_floor, int ele_status, int ele_floor,int last_task_floor)
{
	if (ele_status == PAUSE)
		return abs(user_floor - ele_floor);
	else if (user_choice == ele_status && ((user_choice == UP && user_floor >= ele_floor) || (user_choice == DOWN && user_floor <= ele_floor)))
		return abs(user_floor - ele_floor);
	else//其他情况
		return abs(last_task_floor - user_floor) + abs(last_task_floor + ele_floor);
}
void outside::select_outside(int choice, int floor)
{
	ui.label->setText("Have received request from Floor " + QString::number(floor + 1, 10));
	//选出没有损坏的电梯
	enabled_elevators.clear();
	for (int i = 0; i < ELEVATOR_NUM; i++)
	{
		if (elevators[i]->is_available == YES)
			enabled_elevators.push_back(i);
	}
	ele_priority.clear();
	for (int i : enabled_elevators) {
		if(elevators[i]->status!=PAUSE)
		    ele_priority.push_back({ i, priority_cal(choice, floor, elevators[i]->status, elevators[i]->currentFloor, elevators[i]->dest_inside.back()) });
		else//暂停时elevators[i]->dest_inside.back()为空
			ele_priority.push_back({ i, priority_cal(choice, floor, elevators[i]->status, elevators[i]->currentFloor, elevators[i]->currentFloor) });
	}
	sort(ele_priority.begin(), ele_priority.end(),
		[](pair<int, int>& a, pair<int, int>& b) {return a.second < b.second;});
	ui.label->setText("Elavator" + QString::number(ele_priority[0].first+1, 10) + " is ready for Floor" + QString::number(floor + 1, 10));
	Os1* best_elevator;
	best_elevator = elevators[ele_priority[0].first];
	//将当前楼层添加到电梯的任务队列里，相当于对应的电梯内部有人按了当前floor楼层的按钮
	best_elevator->task_inside(ele_priority[0].first,floor);
}
void outside::refresh()
{
	for (int i = 0; i < ELEVATOR_NUM; i++)
	{
		if (elevators[i]->is_run_pause == YES)
		{
			floorBtnsUp[elevators[i]->currentFloor]->setStyleSheet("");
			floorBtnsUp[elevators[i]->currentFloor]->setEnabled(true);
			floorBtnsDown[elevators[i]->currentFloor]->setStyleSheet("");
			floorBtnsDown[elevators[i]->currentFloor]->setEnabled(true);
		}
	}
}
outside::~outside()
{}
