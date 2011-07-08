/********************************************************************************
** Form generated from reading UI file 'grid_form.ui'
**
** Created: Tue Jul 5 11:52:29 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRID_FORM_H
#define UI_GRID_FORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Grid_Form
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *vlayout;
    QCheckBox *chk_out;
    QCheckBox *chk_in;
    QPushButton *btn_start;

    void setupUi(QWidget *Grid_Form)
    {
        if (Grid_Form->objectName().isEmpty())
            Grid_Form->setObjectName(QString::fromUtf8("Grid_Form"));
        Grid_Form->resize(620, 660);
        verticalLayoutWidget = new QWidget(Grid_Form);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 621, 621));
        vlayout = new QVBoxLayout(verticalLayoutWidget);
        vlayout->setObjectName(QString::fromUtf8("vlayout"));
        vlayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        vlayout->setContentsMargins(0, 0, 0, 0);
        chk_out = new QCheckBox(Grid_Form);
        chk_out->setObjectName(QString::fromUtf8("chk_out"));
        chk_out->setEnabled(false);
        chk_out->setGeometry(QRect(140, 630, 70, 22));
        chk_in = new QCheckBox(Grid_Form);
        chk_in->setObjectName(QString::fromUtf8("chk_in"));
        chk_in->setEnabled(false);
        chk_in->setGeometry(QRect(30, 630, 91, 22));
        btn_start = new QPushButton(Grid_Form);
        btn_start->setObjectName(QString::fromUtf8("btn_start"));
        btn_start->setGeometry(QRect(280, 626, 98, 27));

        retranslateUi(Grid_Form);

        QMetaObject::connectSlotsByName(Grid_Form);
    } // setupUi

    void retranslateUi(QWidget *Grid_Form)
    {
        Grid_Form->setWindowTitle(QApplication::translate("Grid_Form", "Grid", 0, QApplication::UnicodeUTF8));
        chk_out->setText(QApplication::translate("Grid_Form", "Salida", 0, QApplication::UnicodeUTF8));
        chk_in->setText(QApplication::translate("Grid_Form", "Entrada", 0, QApplication::UnicodeUTF8));
        btn_start->setText(QApplication::translate("Grid_Form", "&Start", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Grid_Form: public Ui_Grid_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRID_FORM_H
