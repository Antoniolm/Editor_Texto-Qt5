//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

#include "document.h"


document::document(QTextEdit *panel){
    textPanel=panel;
    isOpen=false;
    isSearch=false;
}

///////////////////////////////
/// \brief document::openDocument
///Método para la guardar los cambios realizados sobre un fichero
///////////////////////////////
void document::saveDocument(){
    //Realizamos la apertura del fichero en modo escritura y con la bandera para reliazar Truncate
    if(!file->open(QFile::WriteOnly| QFile::Truncate | QFile::Text))return;

    //Escribimos en el fichero
    QString texto=textPanel->toPlainText();

    //Realizamos el canal de comunicación y realizamos una escritura en el fichero
    QTextStream out(file);
    out<< texto;

    //Cerramos el fichero
    file->close();

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

/////////////////
/// \brief document::createDocument
/// Método para un nuevo documento, el cual tendra el contenido del
/// textPanel del objeto que lo llama
/// ///////////////////////////////
bool document::createDocument(QString name){
    //Obtenemos el nombre del fichero a partir del path
    path=name;

    //Creamos un QFile con el nombre del fichero seleccionado
    file=new QFile(name+"/"+fileName);

    //Realizamos la apertura del fichero en modo escriturae
    if(!file->open(QFile::WriteOnly | QFile::Text))return false;

    //Realizamos el canal de comunicación y realizamos una escritura en el fichero
    QTextStream out(file);
    out<< textPanel->toPlainText();

    //Cerramos el fichero
    file->close();

    return true;
}

///////////////////////////////////
/// \brief document::search
/// \param elemento Elemento a buscar
/// Método que busca un elemento en nuestro documento
/// ///////////////////////////////
void document::search(QString elemento){
    QString nuevoElemento("<b>"+elemento+"</b>");

    QString texto=textPanel->toPlainText();

    //Realizamos el reemplazo
    texto.replace(elemento,nuevoElemento);
    textPanel->setHtml(texto.replace("\n","<br>"));

    //Actualizamos nuestro bool de estado
    isSearch=true;
}

bool document::isOpenFile(){
    return isOpen;
}

bool document::isSearchFile(){
    return isSearch;
}
QString document::getName(){
    return fileName;
}

QString document::getPath(){
    return path;
}
void document::setPath(QString entrada){
    path=entrada;
}
void document::setName(QString entrada){
    fileName=entrada;
}

void document::desactiveSearch(){
    //Cambiamos el texto de html a texto Plano
    textPanel->setText(textPanel->toPlainText());
    isSearch=false;
}

/////////////////////////
/// \brief document::clear
/// Método para limpiar un documento
//////////////
void document::clear(){
    //Limpiamos todas las variables de nuestro documento
    fileName.clear();
    path.clear();

    file=NULL;
    isOpen=false;
    textPanel->setText("");
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
    for(pos=path.size();pos>0 && !isFinish;pos--){
        if(path[pos]==QLatin1Char('/')){
            salida=path.right((path.size()-pos)-1);
            isFinish=true;
        }

    }

    return  salida;

}
