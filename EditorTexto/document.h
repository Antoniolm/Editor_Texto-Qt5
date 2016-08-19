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
    void saveDocument();
    bool openDocument(QString name);
    bool createDocument(QString name);
    void search(QString);
    void replace(QString,QString);
    bool isOpenFile();
    bool isSearchFile();
    QString getName();
    QString getPath();
    QTextEdit* getTextPanel();
    void setPath(QString);
    void setName(QString);
    void desactiveSearch();

    void clear();

private:
    QString extractName(QString path);
    QFile *file;
    QTextEdit *textPanel;
    QString fileName;
    QString path;
    bool isOpen; //Boolean para saber si el el documento tiene un fichero activo
    bool isSearch; //Boolean para saber si se tiene una busqueda activa

};

#endif // DOCUMENT_H
