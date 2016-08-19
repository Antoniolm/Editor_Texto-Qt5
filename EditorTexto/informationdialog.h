//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////


#ifndef INFORMATIONDIALOG_H
#define INFORMATIONDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class InformationDialog;
}

class InformationDialog : public QDialog
{
    Q_OBJECT
public:
    explicit InformationDialog(QString,QString);
    ~InformationDialog();

signals:

public slots:

private:
    Ui::InformationDialog *ui;
};

#endif // INFORMATIONDIALOG_H
