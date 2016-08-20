//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

#ifndef FONTDIALOG_H
#define FONTDIALOG_H

#include <QDialog>
#include <QString>
#include <mainwindow.h>

namespace Ui{
class FontDialog;
}

class FontDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FontDialog(MainWindow *main);
    ~FontDialog();

signals:

public slots:

private slots:
    void on_pushButton_clicked();

private:
    Ui::FontDialog *ui;
    MainWindow *mainwindow;
};

#endif // FONTDIALOG_H
