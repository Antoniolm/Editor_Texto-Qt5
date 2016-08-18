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

class NameFileDialog : public QDialog
{
    Q_OBJECT
public:
    NameFileDialog(document *docu,QString nameWindow,QString textLabel);
    ~NameFileDialog();

signals:

public slots:

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
    document *doc;

};

#endif // NAMEFILEDIALOG_H
