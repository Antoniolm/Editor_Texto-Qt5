#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCursor>
#include <QString>
#include <QFileDialog>
#include <QTextStream>

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
    existFile=false;
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

////////////////////////////////////////////////
/// \brief MainWindow::on_actionNew_File_triggered
/// /// Método activado cuando se pulsa el boton New File
/// Permite al usuario abrir una nueva ventana del editor
///////////////////////////////////////////////////////////////
void MainWindow::on_actionNew_File_triggered()
{
    //Creamos una nueva ventana
    MainWindow * window = new MainWindow();
    //Hacemos visible la ventana
    window->show();
}

//////////////////////////////////////////////
/// \brief MainWindow::on_actionExit_triggered
/// Método activado cuando se pulsa el boton Exit
/// Permite al usuario cerrar la ventana del editor
/////////////////////////////////////////////
void MainWindow::on_actionExit_triggered()
{
    //Cerramos la ventana
    close();
}

///////////////////////////////////////
/// \brief MainWindow::on_actionClose_file_triggered
/// Método activado cuando se pulsa el boton Close file
/// Permite al usuario cerrar un fichero que este abierto
/////////////////////////////////////////
void MainWindow::on_actionClose_file_triggered()
{
    //Vaciamos nuestro mainText del contenido del fichero
    ui->mainText->setText("");

    //Cerramos el fichero
    if(existFile && file->isOpen())
        file->close();
    existFile=false;
}

///////////////////////////
/// \brief MainWindow::on_actionOpen_File_triggered
/// Método activado cuando se pulsa el boton Open file
/// Permite al usuario realizar una busqueda de un fichero y cargar su contenido
/// en el editor de Textos
///////////////////////////
void MainWindow::on_actionOpen_File_triggered()
{
    //Lanzamos un QFileDialog y obtenemos el nombre del fichero a abrir
    QString fileName= QFileDialog::getOpenFileName(this,tr("Open file"),"C://","Text files (*.txt)");

    //Creamos un QFile con el nombre del fichero seleccionado
    file=new QFile(fileName);

    //Realizamos la apertura del fichero en modo lectura y escritura
    if(!file->open(QFile::ReadWrite | QFile::Text))return;

    //Realizamos el canal de comunicación y realizamos una lectura del fichero
    QTextStream in(file);
    QString contentFile = in.readAll();

    //Enviamos el texto del documento a nuestro mainText
    ui->mainText->setText(contentFile);
    existFile=true;

}
