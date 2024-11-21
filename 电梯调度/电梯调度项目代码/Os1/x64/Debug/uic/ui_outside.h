/********************************************************************************
** Form generated from reading UI file 'outside.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUTSIDE_H
#define UI_OUTSIDE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_outsideClass
{
public:
    QGroupBox *groupBox;
    QLabel *label;

    void setupUi(QWidget *outsideClass)
    {
        if (outsideClass->objectName().isEmpty())
            outsideClass->setObjectName("outsideClass");
        outsideClass->resize(494, 324);
        groupBox = new QGroupBox(outsideClass);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(30, 30, 421, 251));
        QFont font;
        font.setPointSize(10);
        groupBox->setFont(font);
        groupBox->setFlat(false);
        label = new QLabel(outsideClass);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 300, 511, 16));

        retranslateUi(outsideClass);

        QMetaObject::connectSlotsByName(outsideClass);
    } // setupUi

    void retranslateUi(QWidget *outsideClass)
    {
        outsideClass->setWindowTitle(QCoreApplication::translate("outsideClass", "outside", nullptr));
        groupBox->setTitle(QCoreApplication::translate("outsideClass", "Outside Buttons", nullptr));
        label->setText(QCoreApplication::translate("outsideClass", "Ready", nullptr));
    } // retranslateUi

};

namespace Ui {
    class outsideClass: public Ui_outsideClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUTSIDE_H
