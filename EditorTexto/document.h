#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QFile>
#include <QTextEdit>

class document
{
public:
    document(QTextEdit *);
    void save();
    void openDocument();

private:
    QFile *file;
    QTextEdit *textPanel;

};

#endif // DOCUMENT_H
