#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCursor>
#include <QString>

//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_mainText_cursorPositionChanged()
{
    //Obtenemos el cursor de nuestro QTextEdit
    QTextCursor cursor = ui->mainText->textCursor();
    //Actualizamos la posición del cursor
    ui->state->setText("Rows - "+QString::number(cursor.blockNumber())+" colums - "+ QString::number(cursor.positionInBlock()));
}

void MainWindow::on_actionNew_File_triggered()
{
    //Creamos una nueva ventana
    MainWindow * window = new MainWindow();
    //Hacemos visible la ventana
    window->show();
}

void MainWindow::on_actionExit_triggered()
{
    //Cerramos la ventana
    close();
}

void MainWindow::on_actionClose_file_triggered()
{

}
