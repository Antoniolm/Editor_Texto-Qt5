//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

#ifndef TABLEDIALOG_H
#define TABLEDIALOG_H

#include <QDialog>
#include "document.h"

namespace Ui {
class TableDialog;
}

class TableDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TableDialog(document *docu);
    ~TableDialog();

signals:

public slots:

private slots:
    void on_createTable_clicked();

private:
    Ui::TableDialog *ui;
    document *doc;
};

#endif // TABLEDIALOG_H
