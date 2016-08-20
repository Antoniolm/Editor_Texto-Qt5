//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

#ifndef NAMEFILEDIALOG_H
#define NAMEFILEDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <document.h>

namespace Ui {
class Dialog;
}

//Enum que nos permite realizar diferente usos en
//nuestro namefileDialog.
enum dialogFlag{
    newNameFile,//Para la opcion Save as
    search //Para la opcion search
};

class NameFileDialog : public QDialog
{
    Q_OBJECT
public:
    NameFileDialog(document *docu,QString ,QString ,dialogFlag );
    ~NameFileDialog();


signals:

public slots:

private slots:
    void on_pushButton_clicked();
    void onClose();

private:
    Ui::Dialog *ui;
    document *doc;
    dialogFlag flag;

};

#endif // NAMEFILEDIALOG_H
