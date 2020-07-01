#ifndef CALCWITHGUI_H
#define CALCWITHGUI_H

#include <QtWidgets/QMainWindow>
#include "ui_CalcWithGui.h"
#include <QString>
#include <QDebug>
#include <string>
#include "Calculator.h"
#include "Calculation.h"
#include "RPN.h"
#include "History.h"
#include <stack>

//namespace Ui {
//    class CalcWithGui;
//}

class CalcWithGui : public QMainWindow
{
    Q_OBJECT

public:
    CalcWithGui(QWidget* parent = Q_NULLPTR);

private:
    Ui::CalcWithGuiClass ui;

private slots:
    void button_pressed();
    void on_pushButton_delete_released();
    void on_pushButton_allclear_released();
    void on_pushButton_root_released();
    void on_pushButton_pi_released();
    void on_pushButton_result_released();
    void on_pushButton_up_released();
    void on_pushButton_down_released();
};

#endif // !CALCWITHGUI_H