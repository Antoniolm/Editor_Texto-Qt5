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

//Enum que nos permite realizar diferente formatos
//Para asi poder conocer el tipo de formato que se esta
//introduciendo en ese momento
enum FormatFlag{
    bold,//Para la opcion de negrita
    italic, //Para la opcion de italica
    underline // Para la opcion de subrayado
};

class document
{
public:
    document(QTextEdit *);
    void saveDocument();
    bool openDocument(QString name);
    bool createDocument();
    void search(QString);
    void replace(QString,QString);
    void changeFont(FormatFlag);
    bool isOpenFile();
    bool isSearchFile();
    bool isEmpty();
    QString getName();
    QString getPath();
    QTextEdit* getTextPanel();
    void setPath(QString);
    void setName(QString);
    void desactiveSearch();

    void clear();

private:
    QString extractName(QString path);
    bool detectFormat(FormatFlag flag,QTextCursor *cursor);
    void configureFont(FormatFlag,QTextCharFormat *,bool);

    //void configureFont(FormatFlag,QTextCharFormat,int);
    QFile *file;
    QTextEdit *textPanel;
    QString fileName;
    QString path;
    bool isOpen; //Boolean para saber si el el documento tiene un fichero activo
    bool isSearch; //Boolean para saber si se tiene una busqueda activa

};

#endif // DOCUMENT_H
