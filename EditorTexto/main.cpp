#include "mainwindow.h"
#include <QApplication>

//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow wind;
    wind.show();
    return application.exec();
}
