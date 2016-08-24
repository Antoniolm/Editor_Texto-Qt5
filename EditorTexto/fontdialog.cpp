//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

#include "fontdialog.h"
#include "ui_fontdialog.h"
#include "QFontDatabase"

FontDialog::FontDialog(MainWindow *main) : QDialog(0),ui(new Ui::FontDialog)
{
    mainwindow=main;
    ui->setupUi(this);
    this->setWindowTitle("Visualization Format");

    for(int size=6;size<=18;size++)
        ui->sizefont->addItem(QString::number(size),size);

    QFontDatabase db;
    QStringList families =db.families();

    for(int i=4;i<30;i++){
        ui->familyfont->addItem(families[i]);
    }
}


FontDialog::~FontDialog(){

    delete ui;
}

void FontDialog::on_pushButton_clicked()
{
    //mainwindow->fontChanged(ui->familyfont->currentText(),ui->sizefont->currentData().toInt());
    close();
}
