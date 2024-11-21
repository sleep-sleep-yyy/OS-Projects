/********************************************************************************
** Form generated from reading UI file 'all_in_out.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALL_IN_OUT_H
#define UI_ALL_IN_OUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_all_in_outClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *all_in_outClass)
    {
        if (all_in_outClass->objectName().isEmpty())
            all_in_outClass->setObjectName("all_in_outClass");
        all_in_outClass->resize(1011, 701);
        centralWidget = new QWidget(all_in_outClass);
        centralWidget->setObjectName("centralWidget");
        all_in_outClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(all_in_outClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1011, 22));
        all_in_outClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(all_in_outClass);
        mainToolBar->setObjectName("mainToolBar");
        all_in_outClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(all_in_outClass);
        statusBar->setObjectName("statusBar");
        all_in_outClass->setStatusBar(statusBar);

        retranslateUi(all_in_outClass);

        QMetaObject::connectSlotsByName(all_in_outClass);
    } // setupUi

    void retranslateUi(QMainWindow *all_in_outClass)
    {
        all_in_outClass->setWindowTitle(QCoreApplication::translate("all_in_outClass", "all_in_out", nullptr));
    } // retranslateUi

};

namespace Ui {
    class all_in_outClass: public Ui_all_in_outClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALL_IN_OUT_H
