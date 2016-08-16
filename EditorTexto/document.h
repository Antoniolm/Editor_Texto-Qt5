//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////


#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QFile>
#include <QTextEdit>
#include <QString>
#include <QIODevice>
#include <QTextStream>
#include <QFileDialog>

class document
{
public:
    document(QTextEdit *);
    void save();
    bool openDocument(QString name);
    bool isOpenFile();

private:
    QFile *file;
    QTextEdit *textPanel;
    QString fileName;
    bool isOpen; //Boolean para saber si el el documento tiene un fichero activo

};

#endif // DOCUMENT_H
