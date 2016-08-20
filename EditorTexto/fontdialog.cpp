//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

#include "fontdialog.h"
#include "ui_fontdialog.h"

FontDialog::FontDialog(MainWindow *main) : QDialog(0),ui(new Ui::FontDialog)
{
    mainwindow=main;
    ui->setupUi(this);
    this->setWindowTitle("Visualization Format");
    for(int size=6;size<=18;size++)
        ui->sizefont->addItem(QString::number(size));
}


FontDialog::~FontDialog(){

    delete ui;
}

void FontDialog::on_pushButton_clicked()
{
    QFont font;
    font.setPixelSize((ui->sizefont->currentText()).toInt());
    //mainwindow->fontChanged(font);
    close();
}
