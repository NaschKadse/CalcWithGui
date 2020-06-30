#ifndef CALCWITHGUI_H
#define CALCWITHGUI_H

#include <QtWidgets/QMainWindow>
#include "ui_CalcWithGui.h"

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
    void digit_pressed();
};

#endif // CALCWITHGUI_H