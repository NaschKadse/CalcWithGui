#include "CalcWithGui.h"
#include "OwnException.h"

#include <QtWidgets/QApplication>
#include <QWidget>

/*
Falls Probleme beim include vom DynamicFrontSizeLabel: Pfad anpassenin ui_CalcWithGui.h
#include <C:/Daten/Studium/Uni/2. Semester/Programmieren C++/CalcWithGui/CalcWithGui/src/DynamicFontSizeLabel.h>
*/

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    CalcWithGui gui;
    
    gui.show();
    
    return app.exec();
}
