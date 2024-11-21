/********************************************************************************
** Form generated from reading UI file 'Os1.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OS1_H
#define UI_OS1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Os1Class
{
public:
    QSlider *verticalSlider_currentFloor;
    QLabel *label_NUM_FLOOR;
    QGroupBox *groupBox_destination;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_status;
    QLabel *label_3;
    QLabel *label_door;
    QLabel *label_4;
    QLabel *label_current;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_opendoor;
    QPushButton *pushButton_closedoor;
    QPushButton *pushButton_alert;
    QLabel *label_2;
    QLabel *label_5;

    void setupUi(QWidget *Os1Class)
    {
        if (Os1Class->objectName().isEmpty())
            Os1Class->setObjectName("Os1Class");
        Os1Class->resize(306, 393);
        verticalSlider_currentFloor = new QSlider(Os1Class);
        verticalSlider_currentFloor->setObjectName("verticalSlider_currentFloor");
        verticalSlider_currentFloor->setGeometry(QRect(20, 30, 22, 331));
        verticalSlider_currentFloor->setMinimumSize(QSize(0, 331));
        verticalSlider_currentFloor->setMinimum(1);
        verticalSlider_currentFloor->setMaximum(20);
        verticalSlider_currentFloor->setSingleStep(1);
        verticalSlider_currentFloor->setPageStep(1);
        verticalSlider_currentFloor->setValue(1);
        verticalSlider_currentFloor->setOrientation(Qt::Vertical);
        label_NUM_FLOOR = new QLabel(Os1Class);
        label_NUM_FLOOR->setObjectName("label_NUM_FLOOR");
        label_NUM_FLOOR->setGeometry(QRect(20, 10, 21, 21));
        QFont font;
        font.setFamilies({QString::fromUtf8("\346\200\235\346\272\220\351\273\221\344\275\223")});
        font.setPointSize(12);
        label_NUM_FLOOR->setFont(font);
        groupBox_destination = new QGroupBox(Os1Class);
        groupBox_destination->setObjectName("groupBox_destination");
        groupBox_destination->setGeometry(QRect(60, 10, 231, 201));
        QFont font1;
        font1.setBold(false);
        groupBox_destination->setFont(font1);
        groupBox = new QGroupBox(Os1Class);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(60, 220, 161, 141));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 30, 81, 21));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Microsoft YaHei UI")});
        font2.setPointSize(9);
        font2.setBold(true);
        label->setFont(font2);
        label_status = new QLabel(groupBox);
        label_status->setObjectName("label_status");
        label_status->setGeometry(QRect(95, 30, 61, 21));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 65, 54, 21));
        QFont font3;
        font3.setBold(true);
        label_3->setFont(font3);
        label_door = new QLabel(groupBox);
        label_door->setObjectName("label_door");
        label_door->setGeometry(QRect(95, 65, 81, 21));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 100, 71, 21));
        label_4->setFont(font3);
        label_current = new QLabel(groupBox);
        label_current->setObjectName("label_current");
        label_current->setGeometry(QRect(95, 100, 41, 20));
        groupBox_2 = new QGroupBox(Os1Class);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(230, 230, 61, 130));
        pushButton_opendoor = new QPushButton(groupBox_2);
        pushButton_opendoor->setObjectName("pushButton_opendoor");
        pushButton_opendoor->setGeometry(QRect(10, 10, 41, 31));
        pushButton_closedoor = new QPushButton(groupBox_2);
        pushButton_closedoor->setObjectName("pushButton_closedoor");
        pushButton_closedoor->setGeometry(QRect(10, 50, 41, 31));
        pushButton_alert = new QPushButton(groupBox_2);
        pushButton_alert->setObjectName("pushButton_alert");
        pushButton_alert->setGeometry(QRect(10, 90, 41, 31));
        label_2 = new QLabel(Os1Class);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 360, 21, 16));
        label_2->setFont(font3);
        label_5 = new QLabel(Os1Class);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(60, 370, 231, 16));
        label_5->setFont(font3);

        retranslateUi(Os1Class);

        QMetaObject::connectSlotsByName(Os1Class);
    } // setupUi

    void retranslateUi(QWidget *Os1Class)
    {
        Os1Class->setWindowTitle(QCoreApplication::translate("Os1Class", "Os1", nullptr));
        label_NUM_FLOOR->setText(QCoreApplication::translate("Os1Class", "20", nullptr));
        groupBox_destination->setTitle(QCoreApplication::translate("Os1Class", "Buttons", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Os1Class", "Status", nullptr));
        label->setText(QCoreApplication::translate("Os1Class", "\345\275\223\345\211\215\347\212\266\346\200\201:", nullptr));
        label_status->setText(QCoreApplication::translate("Os1Class", "PAUSE", nullptr));
        label_3->setText(QCoreApplication::translate("Os1Class", "\351\227\250\347\212\266\346\200\201:", nullptr));
        label_door->setText(QCoreApplication::translate("Os1Class", "Closed", nullptr));
        label_4->setText(QCoreApplication::translate("Os1Class", "\345\275\223\345\211\215\346\245\274\345\261\202:", nullptr));
        label_current->setText(QCoreApplication::translate("Os1Class", "1", nullptr));
        groupBox_2->setTitle(QString());
        pushButton_opendoor->setText(QCoreApplication::translate("Os1Class", "\345\274\200\351\227\250", nullptr));
        pushButton_closedoor->setText(QCoreApplication::translate("Os1Class", "\345\205\263\351\227\250", nullptr));
        pushButton_alert->setText(QCoreApplication::translate("Os1Class", "\346\212\245\350\255\246", nullptr));
        label_2->setText(QCoreApplication::translate("Os1Class", " 1", nullptr));
        label_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Os1Class: public Ui_Os1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OS1_H
