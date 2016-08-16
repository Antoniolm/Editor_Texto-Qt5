#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCursor>
#include <QString>
#include <QFileDialog>
#include <QTextStream>
#include <QIODevice>

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

    this->setWindowTitle("Text Editor");
    existFile=false;//I need to review this variable because I think that I dont need it

    //Inicializamos el estado de los botones close and save
    ui->actionClose_file->setEnabled(false);
    ui->actionSave->setEnabled(false);

    QTextEdit *Text=new QTextEdit();
    document newDoc(Text);
    docs.append(newDoc);
    ui->groupQText->addTab(Text,"Untitled.txt");
    //ui->groupQText->currentIndex();

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
/// Permite al usuario abrir una nueva pestaña del editor
///////////////////////////////////////////////////////////////
void MainWindow::on_actionNew_File_triggered()
{
    //Creamos un nuevo document and lo añadimos al QList
    QTextEdit *Text=new QTextEdit();
    document newDoc(Text);
    docs.append(newDoc);

    //Creamos una nueva pestaña
    ui->groupQText->addTab(Text,"Untitled.txt");

    //MainWindow * window = new MainWindow();
    //Hacemos visible la ventana
    //window->show();
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
    existFile=false;

    //Cambiamos el estado de los botones close file and save
    ui->actionClose_file->setEnabled(false);
    ui->actionSave->setEnabled(false);

    //Actualizamos el titulo de la ventana
    this->setWindowTitle("Text Editor");


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
    if(!file->open(QFile::ReadOnly | QFile::Text))return;

    //Realizamos el canal de comunicación y realizamos una lectura del fichero
    QTextStream in(file);
    QString contentFile = in.readAll();

    //Enviamos el texto del documento a nuestro mainText
    ui->mainText->setText(contentFile);
    existFile=true;
    file->close();

    //Cambiamos el estado de los botones Close File y save
    ui->actionClose_file->setEnabled(true);
    ui->actionSave->setEnabled(true);

    //Actualizamos el titulo de nuestra ventana con el nombre del txt
    this->setWindowTitle("Text Editor - "+fileName);

}


/////////////////////////////////
/// \brief MainWindow::on_actionSave_triggered
///  Método activado cuando se pulsa el boton Save
/// Permite al usuario guardar los cambios realizados en el fichero
/////////////////////////////////////////
void MainWindow::on_actionSave_triggered()
{
    //Si existe un fichero
    if(existFile){
        //Realizamos la apertura del fichero en modo escritura y con la bandera para reliazar Truncate
        if(!file->open(QFile::WriteOnly| QFile::Truncate | QFile::Text))return;

        //Escribimos en el fichero
        QString texto=ui->mainText->toPlainText();

        //Realizamos el canal de comunicación y realizamos una escritura en el fichero
        QTextStream out(file);
        out<< texto;

        //Cerramos el fichero
        file->close();
    }
}
/////////////////////////////////
/// \brief MainWindow::on_actionSaveAs_triggered
/// Método activado cuando se pulsa el boton Save
/// Permite al usuario guardar el contenido en un nuevo fichero
///////////////////////////////////
void MainWindow::on_actionSaveAs_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "C://",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);

    //Creamos nuestro nuevo fichero
    file=new QFile(dir+"/File.txt");

    //Realizamos la apertura del fichero en modo escriturae
    if(!file->open(QFile::WriteOnly | QFile::Text))return;

    //Realizamos el canal de comunicación y realizamos una escritura en el fichero
    QTextStream out(file);
    out<< ui->mainText->toPlainText();

    //Cerramos el fichero
    file->close();

    //Cambiamos el estado de los botones Close File y save
    ui->actionClose_file->setEnabled(true);
    ui->actionSave->setEnabled(true);

    //Actualizamos el titulo de nuestra ventana con el nombre del txt
    this->setWindowTitle("Text Editor - "+dir+"/File.txt");
}
