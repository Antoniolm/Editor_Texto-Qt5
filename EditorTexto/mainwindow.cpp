//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <namefiledialog.h>
#include <replacedialog.h>
#include <informationdialog.h>
#include <QFontDatabase>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    title="Yu Editor - ";

    //Inicializamos diferentes variables y opciones
    this->setWindowTitle(title);
    setStyleSheet("QMainWindow {background: #F1F5FC;}");
    ui->formatBar->addStretch(1);
    this->setFocusPolicy(Qt::NoFocus);
    ui->actionSave->setEnabled(false);

    //Creamos un nuevo document y lo añadimos al QList y al QtabWidget
    QTextEdit *Text=new QTextEdit();
    connect(Text,SIGNAL(cursorPositionChanged()),this,SLOT(on_cursorPositionChanged()));
    Text->setFontPointSize(9);

    document newDoc(Text);
    docs.append(newDoc);
    ui->groupQText->addTab(Text,"Untitled.txt");


    //Inicializamos las familias y tamaños disponibles
    for(int size=6;size<=30;size++)
        ui->sizefont->addItem(QString::number(size),size);

    //Añadimos los slot
    connect(ui->sizefont,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_currentSizeChanged()));
    connect(ui->familyfont,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_currentFamilyChanged()));

    QFontDatabase db;
    QStringList families =db.families();

    for(int i=4;i<50;i++){
        ui->familyfont->addItem(families[i]);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


///////////////////////////
/// \brief MainWindow::on_cursorPositionChanged
/// Método que se activara cuando se cambie de posición
/// el cursor dentro del QTextEdit y nos mostrara por pantalla
/// la fila y columna en la que esta posicionado el cursor
//////////////////////////
void MainWindow::on_cursorPositionChanged()
{
    //Obtenemos el cursor de nuestro QTextEdit
    int currentPosition=ui->groupQText->currentIndex();
    QTextCursor cursor = (docs[currentPosition].getTextPanel())->textCursor();

    //Actualizamos botones
    if(docs[currentPosition].isImage()) ui->actionResize_Image->setEnabled(true);
    else ui->actionResize_Image->setEnabled(false);

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
    QTextEdit *Text=new QTextEdit();
    connect(Text,SIGNAL(cursorPositionChanged()),this,SLOT(on_cursorPositionChanged()));

    //Creamos el nuevo doc y le añadimos el QTextEdit ya configurado
    document newDoc(Text);
    docs.append(newDoc);

    //Creamos una nueva pestaña
    ui->groupQText->addTab(Text,"Untitled.txt");
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
    this->setWindowTitle(title);

    //Comprobamos si es la ultima pestaña o no
    if(ui->groupQText->count()!=1){ //Si lo es
        docs.removeAt(currentPosition);
        ui->groupQText->removeTab(currentPosition);
    }
    else{//Si no es la ultima pestaña
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
        this->setWindowTitle(title+fileName);

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

    //Obtenemos el nombre actual(si hay)
    QString oldName=docs[currentPosition].getName();

    //Lanzamos la intefaz de selección de directorio
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "C://",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);

    if(!dir.isEmpty()){//Si no esta vacio
        //Obtenemos el nuevo nombre y creamos el documento con dicho nombre
        NameFileDialog *newdialog=new NameFileDialog(&docs[currentPosition], tr("Name file"),tr("Name"),dialogFlag::newNameFile);
        newdialog->exec();

        if(docs[currentPosition].getName()!=".txt"){
            docs[currentPosition].setPath(dir);
            docs[currentPosition].createDocument();

            //Cambiamos el estado del boton save
            ui->actionSave->setEnabled(true);

            //Actualizamos el titulo de nuestra ventana y de nuestra pestaña con el nombre del txt
            this->setWindowTitle(title+docs[currentPosition].getPath()+"/"+docs[currentPosition].getName());
            ui->groupQText->setTabText(currentPosition,docs[currentPosition].getName());

       }
       else{//Si esta vacio
            docs[currentPosition].setName(oldName);
        }

    }
}

/////////////////////////////////////////////////
/// \brief MainWindow::on_groupQText_currentChanged
/// \param index
/// Método activado cuando realizamos un cambio de pestaña en el elemento groupQText(QTabWdiget)
/// Realizamos una actualización según el contenido de la pestaña seleccionada
//////////////////////////////////////////////////
void MainWindow::on_groupQText_currentChanged(int index)
{
    int currentPosition=ui->groupQText->currentIndex();
    this->setWindowTitle(title+docs[currentPosition].getPath());

    //Actualizamos el estado de ciertos botones dependiendo
    if(docs[currentPosition].isOpenFile()) ui->actionSave->setEnabled(true);
    else ui->actionSave->setEnabled(false);

    if(docs[currentPosition].isSearchFile()){ //Si se ha realizado una busqueda
        docs[currentPosition].desactiveSearch();
    }

    ui->state->setText("Rows -  colums - ");
}

///////////////////////////
/// \brief MainWindow::on_actionSearch_triggered
/// Método activado cuando realizamos una busqueda
/// Busqueda de un elemento en el documento visible actualmente
///////////////////////////
void MainWindow::on_actionSearch_triggered()
{
    int currentPosition=ui->groupQText->currentIndex();

    //Lanzamos nuestro nameFileDialog
    NameFileDialog *newdialog=new NameFileDialog(&docs[currentPosition], tr("Search"),tr("Parameter of search"),dialogFlag::search);
    newdialog->exec();


}

///////////////////////////
/// \brief MainWindow::on_actionReplace_triggered
/// Método activado cuando pulsamos la opción replace
/// Reemplazo de un elemento por otro en el documento
/// que esta visible actualmente
//////////////////////////////////////
void MainWindow::on_actionReplace_triggered()
{
    int currentPosition=ui->groupQText->currentIndex();

    //Lanzamos la interfaz para obtener la información a reemplazar
    ReplaceDialog *replace=new ReplaceDialog(&docs[currentPosition]);
    replace->exec();
}

///////////////////////////////////
/// \brief MainWindow::on_actionAbout_triggered
/// Muestra la version de la aplicación
/////////////////////////////////
void MainWindow::on_actionAbout_triggered()
{
    QString info("Version 1.0.0\n\n "
                 "GNU GENERAL PUBLIC LICENSE\n"
                 " Version 2, June 1991\n"
                 " Copyright (C) 2016");
    InformationDialog *information=new InformationDialog(tr("Version"),info);
    information->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    int currentPosition=ui->groupQText->currentIndex();

    docs[currentPosition].changeFont(FormatFlag::bold);


}

void MainWindow::on_underline_clicked()
{
    int currentPosition=ui->groupQText->currentIndex();

    docs[currentPosition].changeFont(FormatFlag::underline);
}

void MainWindow::on_italic_clicked()
{
    int currentPosition=ui->groupQText->currentIndex();

    docs[currentPosition].changeFont(FormatFlag::italic);
}

//////////////////////////////////
/// \brief MainWindow::on_actionExport_to_pdf_triggered
/// Método el cual nos permite generar un documento pdf a partir de nuestro fichero
/// actualmente visible
//////////////////////////////////
void MainWindow::on_actionExport_to_pdf_triggered()
{
    //Obtenemos el tab actual
    int currentPosition=ui->groupQText->currentIndex();

    //Lanzamos la intefaz de selección de directorio
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "C://",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    //Si no esta vacio
    if(!dir.isEmpty()){
        docs[currentPosition].setPathPdf(dir);

        NameFileDialog *newdialog=new NameFileDialog(&docs[currentPosition], tr("Name file"),tr("Name"),dialogFlag::expPdf);
        newdialog->exec();

    }

}

/////////////////
/// \brief MainWindow::on_currentIndex_Changed
/// Método para detectar un cambio de formato al cambiar en el tamaño
////////////////
void MainWindow::on_currentSizeChanged(){
    int currentPosition=ui->groupQText->currentIndex();

    docs[currentPosition].changeFont(ui->familyfont->currentText(),ui->sizefont->currentText().toInt());

}

/////////////////////
/// \brief MainWindow::on_currentFamilyChanged
/// Método para detectar un cambio de formato al cambiar la familia del texto
/////////////////////
void MainWindow::on_currentFamilyChanged(){
    int currentPosition=ui->groupQText->currentIndex();

    docs[currentPosition].changeFont(ui->familyfont->currentText(),ui->sizefont->currentText().toInt());

}

/////////////////////////
/// \brief MainWindow::on_Right_clicked
/// Método para realizar un cambio de align en el texto seleccionado
/////////////////////////
void MainWindow::on_Right_clicked()
{
    int currentPosition=ui->groupQText->currentIndex();

    docs[currentPosition].changeAlign(AlignFlag::rightAlign);
}

/////////////////////////
/// \brief MainWindow::on_center_clicked
/// Método para realizar un cambio de align en el texto seleccionado
/////////////////////////
void MainWindow::on_center_clicked()
{
    int currentPosition=ui->groupQText->currentIndex();

    docs[currentPosition].changeAlign(AlignFlag::centerAlign);
}

/////////////////////////
/// \brief MainWindow::on_left_clicked
/// Método para realizar un cambio de align en el texto seleccionado
/////////////////////////
void MainWindow::on_left_clicked()
{
    int currentPosition=ui->groupQText->currentIndex();

    docs[currentPosition].changeAlign(AlignFlag::leftAlign);
}


///////////////////////////////////
/// \brief MainWindow::on_actionInsert_Table_triggered
/// Método para a inserción de una tabla en la posición actual del cursor
//////////////////////////////////
void MainWindow::on_actionInsert_Table_triggered()
{
    int currentPosition=ui->groupQText->currentIndex();

    TableDialog *tableDia=new TableDialog(&docs[currentPosition]);
    tableDia->exec();
}


////////////////////////
/// \brief MainWindow::on_actionInsert_Image_triggered
/// Método para a inserción de una imagen en la posición actual del cursor
///////////////////////
void MainWindow::on_actionInsert_Image_triggered()
{
    int currentPosition=ui->groupQText->currentIndex();

    QString fileName= QFileDialog::getOpenFileName(this,tr("Select Image"),"C://","Imagen files (*.jpg)");

    //Si hemos seleccionado un fichero
    if(!fileName.isEmpty()){
        int width=60,height=60;

        ImageDialog *imageDia=new ImageDialog(width,height);
        imageDia->exec();
        width=imageDia->getWidth();
        height=imageDia->getHeight();

        docs[currentPosition].insertImage(fileName,width,height);
    }
}

//////////////////////////////
/// \brief MainWindow::on_actionResize_Image_triggered
///
///
///////////////////////////////
void MainWindow::on_actionResize_Image_triggered()
{
    int currentPosition=ui->groupQText->currentIndex();
    std::pair<int,int> sizeImage;

    if(docs[currentPosition].isImage()){ //Si tenemos seleccionada una imagen
        sizeImage=docs[currentPosition].getSizeImage();
        ImageDialog *imageDia=new ImageDialog(sizeImage.first,sizeImage.second);
        imageDia->exec();
        docs[currentPosition].setSizeImage(imageDia->getHeight(),imageDia->getWidth());
    }
}
