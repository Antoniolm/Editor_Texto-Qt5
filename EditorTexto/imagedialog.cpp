//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

#include "imagedialog.h"
#include "ui_imagedialog.h"

ImageDialog::ImageDialog(int imageWidth, int imageHeight) : QDialog(0),ui(new Ui::ImageDialog)
{
    ui->setupUi(this);
    ui->height->setMaximum(1000);
    ui->height->setValue(imageHeight);
    ui->width->setMaximum(800);
    ui->width->setValue(imageWidth);
}
ImageDialog::~ImageDialog(){
    delete ui;
}

void ImageDialog::on_pushButton_clicked()
{
    close();
}

int ImageDialog::getHeight(){
    return ui->height->value();
}

int ImageDialog::getWidth(){
    return ui->width->value();
}
