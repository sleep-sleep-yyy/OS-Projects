#pragma once

#include "Os1.h"
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <QLabel>
#include <QString>
#include <QStatusBar>
#include "ui_outside.h"
using namespace std;
class outside : public QWidget
{
	Q_OBJECT

public:
	outside(QWidget* parent = nullptr, vector<Os1*> Elevators = {},int floor_num = 20);
	~outside();

private:
	Ui::outsideClass ui;
public:
	QTimer* timer2;
	vector<Os1*> elevators;//�����б�
	vector<int>enabled_elevators;//���õ����б����
	vector<pair<int, int>> ele_priority;//ÿ�����ݵ����ȶ�
	////ÿ����������°�ť
	vector<QPushButton*> floorBtnsUp;
	vector<QPushButton*> floorBtnsDown;
public:
	void select_outside(int choice, int floor);
	int priority_cal(int user_choice,int user_floor,int ele_status,int ele_floor, int last_task_floor);
	void refresh();
};
