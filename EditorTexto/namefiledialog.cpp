//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

#include "namefiledialog.h"
#include "ui_namefiledialog.h"

NameFileDialog::NameFileDialog(QDialog *parent) : QDialog(parent),ui(new Ui::Dialog)
{
   ui->setupUi(this);
}

NameFileDialog::~NameFileDialog(){
    delete ui;
}

void NameFileDialog::on_pushButton_clicked()
{

}
