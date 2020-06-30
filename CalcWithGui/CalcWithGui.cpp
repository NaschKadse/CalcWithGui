#include "CalcWithGui.h"
#include <QString>
#include <QDebug>

CalcWithGui::CalcWithGui(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.pushButton_0, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui.pushButton_1, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui.pushButton_2, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui.pushButton_3, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui.pushButton_4, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui.pushButton_5, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui.pushButton_6, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui.pushButton_7, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui.pushButton_8, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui.pushButton_9, SIGNAL(released()), this, SLOT(digit_pressed()));
}


void CalcWithGui::digit_pressed()
{
    QPushButton* button = (QPushButton*)sender();

    double label_term;
    QString newLabel;

    label_term = (ui.label_term->text() + button->text()).toDouble();

    newLabel = QString::number(label_term, 'g', 15);

    ui.label_term->setText(newLabel);
    //qDebug() << "test";
}