#include "CalcWithGui.h"
#include <QtWidgets/QApplication>
#include <QWidget>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    CalcWithGui w;
    w.show();
    return a.exec();
}
