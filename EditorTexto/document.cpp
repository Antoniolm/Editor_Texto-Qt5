//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

#include "document.h"



document::document(QTextEdit *panel){
    textPanel=panel;
    isOpen=false;
}

void document::save(){


}
bool document::openDocument(QString name){

    //Inicializamos fileName
    fileName=name;

    //Creamos un QFile con el nombre del fichero seleccionado
    file=new QFile(fileName);

    //Realizamos la apertura del fichero en modo lectura y escritura
    if(!file->open(QFile::ReadOnly | QFile::Text))return false;

    //Realizamos el canal de comunicación y realizamos una lectura del fichero
    QTextStream in(file);
    QString contentFile = in.readAll();

    //Enviamos el texto del documento a nuestro mainText
    textPanel->setText(contentFile);
    isOpen=true;
    file->close();

    return true;

}

/*bool documento::closeDocument(){


}*/

bool document::isOpenFile(){
    return isOpen;
}
