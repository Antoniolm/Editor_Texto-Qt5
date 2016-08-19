//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

#include "informationdialog.h"
#include "ui_informationdialog.h"

InformationDialog::InformationDialog(QString title,QString texto) : QDialog(0),ui(new Ui::InformationDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(title);
    ui->label->setText(texto);
    ui->label->setAlignment(Qt::AlignCenter);
}

InformationDialog::~InformationDialog(){
    delete ui;
}
