//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

#include "namefiledialog.h"
#include "ui_namefiledialog.h"

NameFileDialog::NameFileDialog(document *docu,QString nameWindow,QString textLabel) : QDialog(0),ui(new Ui::Dialog)
{
   doc=docu;
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
    doc->setName(ui->textEdit->text()+".txt");
    close();
}
