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

///////////////////////////////
/// \brief document::openDocument
///Método para la apertura del fichero de un objeto documento
///////////////////////////////
bool document::openDocument(QString name){

    //Obtenemos el nombre del fichero a partir del path
    fileName=extractName(name);
    path=name;

    //Creamos un QFile con el nombre del fichero seleccionado
    file=new QFile(name);

    //Realizamos la apertura del fichero en modo lectura y escritura
    if(!file->open(QFile::ReadOnly | QFile::Text))return false;

    //Realizamos el canal de comunicación y realizamos una lectura del fichero
    QTextStream in(file);
    QString contentFile = in.readAll();

    //Enviamos el texto del documento a nuestro mainText
    textPanel->setText(contentFile);
    isOpen=true;

    //Cerramos el fichero
    file->close();

    return true;

}

/*bool documento::closeDocument(){


}*/

bool document::isOpenFile(){
    return isOpen;
}

QString document::getName(){
    return fileName;
}

QString document::getPath(){
    return path;
}
/////////////////////////
/// \brief document::clear
/// Método para limpiar un documento
//////////////
void document::clear(){
    /*fileName.clear();
    path.clear();
    delete(file);
    isOpen=false;
    textPanel->setText("");*/
}

////////////////////////////////
/// \brief document::extractName
/// Método que nos permite extraer el nombre del fichero
/// desde del path de dicho fichero
/////////////////////////////
QString document::extractName(QString path){
    QString salida;
    int pos;
    bool isFinish=false;

    //Recorremos nuestro path hasta encontrar un '/'
    //Una vez encontrado extraemos el nombre del fichero
    for(pos=0;pos<path.size()&& !isFinish;pos++){
        if(path[pos]==QLatin1Char('/')){
            salida=path.right((path.size()-pos)-1);
            isFinish=true;
        }

    }

    return  salida;

}
