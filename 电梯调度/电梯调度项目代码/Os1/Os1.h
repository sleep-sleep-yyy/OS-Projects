#pragma once

#include <QtWidgets/QWidget>
#include "ui_Os1.h"
#include <vector>
//#include <algorithm>
#include <QTimer>
#include <QGroupBox>
#include <QMessageBox>
#include <QPushButton>
#include <QElapsedTimer>

/// <summary>
/// 电梯内部
/// </summary>
#define PAUSE 0
#define UP 1
#define DOWN 2
#define CLOSED 0
#define OPEN 1
#define YES 1
#define NO 0
#define FLOOR_NUM 20
#define ELEVATOR_NUM 5
class Os1 : public QWidget
{
    Q_OBJECT

public:
    //以电梯序号和楼层数进行初始化
    Os1(QWidget *parent = nullptr, int elevator_id = 0, int floor_num = 20);
    ~Os1();

private:
    Ui::Os1Class ui;

public:
    QTimer* timer;//计时器
    int door = CLOSED; //电梯门的状态
    int status = PAUSE; //电梯状态 [0: pause,1: up ，2: down].
    int is_available = YES;//电梯是否可用
    int is_run_pause = NO;//电梯是否是在运行中经过途径点暂缓
    int currentFloor = 0;//电梯当前楼层
    std::vector<int>dest_inside;//电梯当前执行的顺路的任务队列
    std::vector<int>dest_inside_no;//与当前运行方向不一致的任务队列
    QString statusStr[3] = { "PAUSE", "UP", "DOWN" };
    QString doorStr[2] = { "Closed", "Open" };
    std::vector<QPushButton*> buttons;
    void refresh_label();//label的更新
    void task_inside(int elevator_id, int destnation_id);//电梯内乘客选择目的地
    void to_run();//电梯运行
    void open_door();//门的打开与关闭，模拟乘客进出
    void refresh();//电梯状态更新
};
