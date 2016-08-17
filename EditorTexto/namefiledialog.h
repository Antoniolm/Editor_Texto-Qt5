//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

#ifndef NAMEFILEDIALOG_H
#define NAMEFILEDIALOG_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class Dialog;
}

class NameFileDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NameFileDialog(QDialog *parent = 0);
    ~NameFileDialog();

signals:

public slots:

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // NAMEFILEDIALOG_H
