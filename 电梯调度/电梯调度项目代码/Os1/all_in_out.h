#pragma once
#include "windows.h"
#include "outside.h"
#include <QCloseEvent>
#include <QMainWindow>
//#include "ui_all_in_out.h"

class all_in_out : public QMainWindow
{
public:
	all_in_out(QWidget *parent = nullptr);
	~all_in_out();
	std::vector<Os1*> elevators; // Used to store elevators, it should be empty before every simulation.
};
