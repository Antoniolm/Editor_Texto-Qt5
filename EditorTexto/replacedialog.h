//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////


#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>
#include <document.h>

namespace Ui {
class ReplaceDialog;
}


class ReplaceDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ReplaceDialog(document *docu);
    ~ReplaceDialog();
signals:

public slots:

private slots:
    void on_pushButton_clicked();

private:
    Ui::ReplaceDialog *ui;
    document *doc;
};

#endif // REPLACEDIALOG_H
