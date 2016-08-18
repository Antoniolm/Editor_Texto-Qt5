//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <namefiledialog.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    //Inicializamos diferentes variables y opciones
    this->setWindowTitle("Text Editor");
    existFile=false;//I need to review this variable because I think that I dont need it

    //Inicializamos el estado de los botones close and save
    ui->actionSave->setEnabled(false);

    QTextEdit *Text=new QTextEdit();
    document newDoc(Text);
    docs.append(newDoc);
    ui->groupQText->addTab(Text,"Untitled.txt");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_mainText_cursorPositionChanged()
{
    //Obtenemos el cursor de nuestro QTextEdit
    //QTextCursor cursor = ui->mainText->textCursor();
    //Actualizamos la posición del cursor
    //ui->state->setText("Rows - "+QString::number(cursor.blockNumber())+" colums - "+ QString::number(cursor.positionInBlock()));
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
    //Incrementamos el contador
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
    int currentPosition=ui->groupQText->currentIndex();
    this->setWindowTitle("Text Editor");

    //Comprobamos si es la ultima pestaña o no
    //Ya que si es la ultima pestaña no se eliminara sino que se
    //limpiara la información de ella
    if(ui->groupQText->count()!=1){

        //eliminamos del QList el docs
        docs.removeAt(currentPosition);

        //Eliminamos la pestaña
        ui->groupQText->removeTab(currentPosition);
    }
    else{
        docs[currentPosition].clear(); //reInicializamos el documento
        ui->groupQText->setTabText(currentPosition,"Untitled.txt"); //Ponemos el nombre por defecto del fichero
    }
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
    QString fileName= QFileDialog::getOpenFileName(this,tr("Open File"),"C://","Text files (*.txt)");

    //Si hemos seleccionado un fichero
    if(!fileName.isEmpty()){
        int currentPosition=ui->groupQText->currentIndex();
        docs[currentPosition].openDocument(fileName);

        //Cambiamos el estado de los botones Close File y save
        ui->actionSave->setEnabled(true);

        //Actualizamos el titulo de nuestra ventana con el nombre del txt
        this->setWindowTitle("Text Editor - "+fileName);

        //Actualizamos el nombre de la pestaña con el nombre del fichero actual
        ui->groupQText->setTabText(currentPosition,docs[currentPosition].getName());
    }
}


/////////////////////////////////
/// \brief MainWindow::on_actionSave_triggered
///  Método activado cuando se pulsa el boton Save
/// Permite al usuario guardar los cambios realizados en el fichero
/////////////////////////////////////////
void MainWindow::on_actionSave_triggered()
{
    int currentPosition=ui->groupQText->currentIndex();
    docs[currentPosition].saveDocument();
}
/////////////////////////////////
/// \brief MainWindow::on_actionSaveAs_triggered
/// Método activado cuando se pulsa el boton Save
/// Permite al usuario guardar el contenido en un nuevo fichero
///////////////////////////////////
void MainWindow::on_actionSaveAs_triggered()
{
    //Obtenemos el tab actual
    int currentPosition=ui->groupQText->currentIndex();

    //Lanzamos la intefaz de selección de directorio
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "C://",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    NameFileDialog *newdialog=new NameFileDialog(&docs[currentPosition], tr("Name file"),tr("Name"));
    newdialog->exec();

    //Creamos el nuevo documento
    docs[currentPosition].createDocument(dir);

    //Cambiamos el estado de los botones save
    ui->actionSave->setEnabled(true);

    //Actualizamos el titulo de nuestra ventana y de nuestra pestaña con el nombre del txt
    this->setWindowTitle("Text Editor - " +docs[currentPosition].getPath());
    ui->groupQText->setTabText(currentPosition,docs[currentPosition].getName());
}

/////////////////////////////////////////////////
/// \brief MainWindow::on_groupQText_currentChanged
/// \param index
/// Método activado cuando realizamos un cambio de pestaña en el elemento groupQText(QTabWdiget)
/// Realizamos una actualización según el contenido de la pestaña seleccionada
//////////////////////////////////////////////////
void MainWindow::on_groupQText_currentChanged(int index)
{
    //Obtenemos la posición actual del Tab widget
    int currentPosition=ui->groupQText->currentIndex();

    //Actualizamos el titulo de la ventana principal
    this->setWindowTitle("Text Editor - "+docs[currentPosition].getPath());

    //Actualizamos el estado de ciertos botones dependiendo
    //de si el documento actual tiene o no fichero abierto
    if(docs[currentPosition].isOpenFile()){
        ui->actionSave->setEnabled(true);
    }
    else{
        ui->actionSave->setEnabled(false);
    }
}
