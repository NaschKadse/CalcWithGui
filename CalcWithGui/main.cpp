#include "CalcWithGui.h"
#include <QtWidgets/QApplication>
#include <QWidget>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    CalcWithGui gui;
    gui.show();
    return app.exec();
}
