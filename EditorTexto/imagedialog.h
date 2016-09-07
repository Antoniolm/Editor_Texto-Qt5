//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

#ifndef IMAGEDIALOG_H
#define IMAGEDIALOG_H

#include <QDialog>

namespace Ui {
class ImageDialog;
}

class ImageDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ImageDialog(int,int);
    ~ImageDialog();
    int getHeight();
    int getWidth();

signals:

public slots:

private slots:
    void on_pushButton_clicked();

private:
    Ui::ImageDialog *ui;
};

#endif // IMAGEDIALOG_H
