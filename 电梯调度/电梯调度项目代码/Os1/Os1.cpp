#include "Os1.h"

Os1::Os1(QWidget* parent, int elevator_id, int floor_num) : QWidget(parent)
{
	ui.setupUi(this);
	QGroupBox* box = ui.groupBox_destination;
	for (int i = 0; i < floor_num; i++) {
		QPushButton* btn = new QPushButton(box);
		btn->setGeometry(20 + 40 * (i % 5) + 210 * (i / 20), 30 + 40 * (i % 20 / 5), 30, 30);
		btn->setText(QString::number(i + 1, 10));
		btn->show();
		connect(btn, &QPushButton::clicked,[=] {
			btn->setStyleSheet("background-color: rgb(84, 255, 159);");
			btn->setEnabled(false);
			//按键处理函数
			bool ok;
			task_inside(elevator_id, btn->text().toInt(&ok)-1);
			});
		buttons.push_back(btn);
	}
	this->setWindowTitle("Elevator: " + QString::number(elevator_id + 1, 10));
	//开门、关门、警报按钮
	connect(ui.pushButton_opendoor, &QPushButton::clicked, [=](void) {
		if(status==PAUSE)
		    door = OPEN;
		refresh_label();
		});
	connect(ui.pushButton_closedoor, &QPushButton::clicked, [=] {door = CLOSED; });
	connect(ui.pushButton_alert, &QPushButton::clicked,  [=] { 
		ui.pushButton_alert->setStyleSheet("background-color: rgb(180, 0, 0);");
		QMessageBox::about(nullptr, "Danger!", "Alert!!");
		ui.pushButton_alert->setEnabled(false);
		for (int i = 0;i<FLOOR_NUM;i++)
		{
			buttons[i]->setEnabled(false);
		}
		ui.label_5->setText("The elevator is DISABLED!!!");
		is_available = NO;
		});
	ui.label_5->setText("The elevator is ready");
	QTimer* timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &Os1::refresh);
	timer->start(800);
}
void Os1::task_inside(int elevator_id,int destnation_id)
{
	if (currentFloor <= destnation_id)
	{
		if (status == PAUSE)
			dest_inside.push_back(destnation_id);
		else if (status == UP)
		{
			dest_inside.push_back(destnation_id);
			sort(dest_inside.begin(), dest_inside.end());//从小到大
		}
		else//status==DOWN
		{
			dest_inside_no.push_back(destnation_id);
			sort(dest_inside_no.begin(), dest_inside_no.end());
		}
	}
	else if (currentFloor > destnation_id)
	{
		if (status == PAUSE)
			dest_inside.push_back(destnation_id);
		else if (status == DOWN)
		{
			dest_inside.push_back(destnation_id);
			sort(dest_inside.begin(), dest_inside.end(), [](int a, int b) {return a > b; });//从大到小
		}
		else//status==UP
		{
			dest_inside_no.push_back(destnation_id);
			sort(dest_inside_no.begin(), dest_inside_no.end(), [](int a, int b) { return a > b; });
		}
	}
}
void Os1::open_door()
{
	is_run_pause = YES;
	door = OPEN;
	refresh_label();
	ui.label_5->setText("Door is open,with people in and out");
	QElapsedTimer t1;
	t1.start();
	while (t1.elapsed() < 2000) QCoreApplication::processEvents();
	door = CLOSED;
	refresh_label();
	ui.label_5->setText("Door is closed");
	is_run_pause = NO;
}
void Os1::to_run()
{
	if (dest_inside.empty() && dest_inside_no.empty())
		status = PAUSE;
	else if (!dest_inside.empty())
	{
		if (currentFloor < dest_inside[0])//则电梯上升
		{
			ui.label_5->setText("The elevator is up");
			status = UP;
			currentFloor++;
		}
		if (currentFloor > dest_inside[0])
		{
			ui.label_5->setText("The elevator is down");
			status = DOWN;
			currentFloor--;
		}
		if (currentFloor == dest_inside[0])
		{
			open_door();
			while (!dest_inside.empty()&&currentFloor == dest_inside[0])//因为可能会楼层重复
				dest_inside.erase(dest_inside.begin());//删除当前楼层的任务
			if (dest_inside.empty())
				status = PAUSE;
			buttons[currentFloor]->setEnabled(true);
			buttons[currentFloor]->setStyleSheet("");
		}
	}
	else if (dest_inside.empty() && !dest_inside_no.empty())//一个方向跑到头了
	{
		dest_inside = dest_inside_no;
		dest_inside_no.clear();
	}
}
void Os1::refresh_label() 
{
	ui.label_status->setText(statusStr[status]);
	ui.label_door->setText(doorStr[door]);
	ui.label_current->setText(QString::number(currentFloor + 1, 10));
	//ui.label_2->setText(QString::number(currentFloor + 1, 10));
	ui.verticalSlider_currentFloor->setValue(currentFloor + 1);
}
void Os1::refresh()//电梯运行以及更新标签操作
{
	to_run();
	refresh_label();
}
Os1::~Os1()
{}
