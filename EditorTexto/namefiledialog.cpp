//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

#include "namefiledialog.h"
#include "ui_namefiledialog.h"

NameFileDialog::NameFileDialog(document *docu,QString nameWindow,QString textLabel,dialogFlag myFlag) : QDialog(0),ui(new Ui::Dialog)
{
   doc=docu;
   flag=myFlag;
   ui->setupUi(this);
   this->setWindowTitle(nameWindow);
   ui->label->setText(textLabel);
}

NameFileDialog::~NameFileDialog(){
    delete ui;
}

/////////////////////////////
/// \brief NameFileDialog::on_pushButton_clicked
/// Método activado cuando se pulsa el boton de accept
/// Obtenemos el nombre indicado y lo enviamos al documento
///////////////////////////////
void NameFileDialog::on_pushButton_clicked()
{
    switch(flag){
    case dialogFlag::newNameFile: //Caso-> opcion Save AS
        doc->setName(ui->textEdit->text()+".txt");
        break;
    case dialogFlag::search: //Caso -> opción search
        doc->search(ui->textEdit->text());
        break;
    }

    //Cerramos la interfaz
    close();
}
