//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////


#include "replacedialog.h"
#include <ui_replacedialog.h>

ReplaceDialog::ReplaceDialog(document *docu) : QDialog(0),ui(new Ui::ReplaceDialog)
{
    doc=docu;
    ui->setupUi(this);
    this->setWindowTitle("Replace dialog");
}


ReplaceDialog::~ReplaceDialog(){
    delete ui;
}

//////////////////////////////////
/// \brief ReplaceDialog::on_pushButton_clicked
/// Método llamado cuando se pulse el boton de replace
/// El cual realizara un reemplazo de elementos en el documento
/// visible actualmente
/// ////////////////////////////
void ReplaceDialog::on_pushButton_clicked(){

    //Si el elemento que queremos cambiar contiene algo
    if(!(ui->oldElement->text()).isEmpty()){
        doc->replace(ui->oldElement->text(),ui->newElement->text());
    }
    close();
}
