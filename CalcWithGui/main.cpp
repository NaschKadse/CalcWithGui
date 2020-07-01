#include "CalcWithGui.h"
#include "OwnException.h"
#include <QtWidgets/QApplication>
#include <QWidget>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    CalcWithGui gui;

    try {
        gui.show();
    }
    catch (exception)
    {

    }
    return app.exec();
}
