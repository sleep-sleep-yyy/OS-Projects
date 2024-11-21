#include "outside.h"

outside::outside(QWidget* parent, vector<Os1*> Elevators, int floor_num): QWidget(parent)
{
	ui.setupUi(this);
	elevators = Elevators;//�ڴ˶�elevators���и�ֵ����ʱ�ڲ��Ѿ���5��������
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
//������������������ۣ��ܽ��ֻ���ڣ�1�����ݿ��У�2����������������������������з���һ�������ڵ������з����� ʱ�������Ϊ/user_floor-ele_floor/
//���������Ϊ/last_task_floor-user_floor/+/last_task_floor+ele_floor/
//�ɴ˼������ȶ�
int outside::priority_cal(int user_choice, int user_floor, int ele_status, int ele_floor,int last_task_floor)
{
	if (ele_status == PAUSE)
		return abs(user_floor - ele_floor);
	else if (user_choice == ele_status && ((user_choice == UP && user_floor >= ele_floor) || (user_choice == DOWN && user_floor <= ele_floor)))
		return abs(user_floor - ele_floor);
	else//�������
		return abs(last_task_floor - user_floor) + abs(last_task_floor + ele_floor);
}
void outside::select_outside(int choice, int floor)
{
	ui.label->setText("Have received request from Floor " + QString::number(floor + 1, 10));
	//ѡ��û���𻵵ĵ���
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
		else//��ͣʱelevators[i]->dest_inside.back()Ϊ��
			ele_priority.push_back({ i, priority_cal(choice, floor, elevators[i]->status, elevators[i]->currentFloor, elevators[i]->currentFloor) });
	}
	sort(ele_priority.begin(), ele_priority.end(),
		[](pair<int, int>& a, pair<int, int>& b) {return a.second < b.second;});
	ui.label->setText("Elavator" + QString::number(ele_priority[0].first+1, 10) + " is ready for Floor" + QString::number(floor + 1, 10));
	Os1* best_elevator;
	best_elevator = elevators[ele_priority[0].first];
	//����ǰ¥����ӵ����ݵ����������൱�ڶ�Ӧ�ĵ����ڲ����˰��˵�ǰfloor¥��İ�ť
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
