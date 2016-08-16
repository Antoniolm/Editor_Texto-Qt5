//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

#include "mainwindow.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow wind;
    wind.show();
    return application.exec();
}
