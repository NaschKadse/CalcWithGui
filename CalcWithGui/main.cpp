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
    catch (const OwnException & e)
    {
        std::cout << e.what() << endl;
    }
    catch (std::exception e)
    {
        std::cout << "Unknown Error: " << e.what() << endl;
    }
    return app.exec();
}
