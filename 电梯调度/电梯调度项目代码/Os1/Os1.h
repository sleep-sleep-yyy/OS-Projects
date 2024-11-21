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
/// �����ڲ�
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
    //�Ե�����ź�¥�������г�ʼ��
    Os1(QWidget *parent = nullptr, int elevator_id = 0, int floor_num = 20);
    ~Os1();

private:
    Ui::Os1Class ui;

public:
    QTimer* timer;//��ʱ��
    int door = CLOSED; //�����ŵ�״̬
    int status = PAUSE; //����״̬ [0: pause,1: up ��2: down].
    int is_available = YES;//�����Ƿ����
    int is_run_pause = NO;//�����Ƿ����������о���;�����ݻ�
    int currentFloor = 0;//���ݵ�ǰ¥��
    std::vector<int>dest_inside;//���ݵ�ǰִ�е�˳·���������
    std::vector<int>dest_inside_no;//�뵱ǰ���з���һ�µ��������
    QString statusStr[3] = { "PAUSE", "UP", "DOWN" };
    QString doorStr[2] = { "Closed", "Open" };
    std::vector<QPushButton*> buttons;
    void refresh_label();//label�ĸ���
    void task_inside(int elevator_id, int destnation_id);//�����ڳ˿�ѡ��Ŀ�ĵ�
    void to_run();//��������
    void open_door();//�ŵĴ���رգ�ģ��˿ͽ���
    void refresh();//����״̬����
};
