//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

#include "document.h"
#include <QtPrintSupport/QPrinter>
#include <QDebug>
#include <QTextTable>
#include <QImage>

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
    if(isSearch)
        desactiveSearch();

    //Realizamos la apertura del fichero en modo escritura y con la bandera para reliazar Truncate
    if(!file->open(QFile::WriteOnly| QFile::Truncate | QFile::Text))return;

    //Escribimos en el fichero
    QString texto=textPanel->toHtml();

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


    file=new QFile(name);
    if(!file->open(QFile::ReadOnly | QFile::Text))return false;
    QTextStream in(file);
    QString contentFile = in.readAll();

    //Enviamos el texto del documento a nuestro mainText
    textPanel->setHtml(contentFile);
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
bool document::createDocument(){
    if(isSearch) desactiveSearch();
    //Creamos un QFile con el nombre del fichero seleccionado
    file=new QFile(path+"/"+fileName);

    if(!file->open(QFile::WriteOnly | QFile::Text))return false;
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
    if(isSearch){
        desactiveSearch();
    }
    QString nuevoElemento("<span style='background: yellow'>"+elemento+"</span>");
    elementSearch=elemento;
    elementWithHtml=nuevoElemento;

    QString texto=textPanel->toHtml();

    //Realizamos el reemplazo
    texto.replace(elemento,nuevoElemento);
    textPanel->setHtml(texto);
    isSearch=true;
}

///////////////////////////////
/// \brief document::replace
/// Método para reemplazar un conjunto de caracteres por otro
/// en nuestro documento
/////////////////////////
void document::replace(QString oldElement, QString newElement){
    QString texto=textPanel->toHtml();
    texto.replace(oldElement,newElement);
    textPanel->setHtml(texto);

}

/////////////////////////////////////
/// \brief document::changeFont
/// Método para el cambio de formato del texto o de un fragmento de el
////////////////////////////////////
void document::changeFont(FormatFlag flag){
    //Cursor utilizado para realizar el cambio de formato
    QTextCursor cursor(textPanel->textCursor());

    //Cursor para checkear correctamente el formato actual del texto
    QTextCursor checkCursor(textPanel->textCursor());
    QString texto;

    //Cambiamos la posición de este cursor auxiliar para las comprobaciones de formato
    checkCursor.setPosition(cursor.selectionStart()+1,QTextCursor::MoveAnchor);
    checkCursor.setPosition(cursor.selectionEnd(),QTextCursor::KeepAnchor);
    QTextCharFormat font(checkCursor.charFormat());

    //Comprobamos si el texto esta en underline
    if(detectFormat(flag,&checkCursor)){
        configureFont(flag,&font,false);
        cursor.setCharFormat(font);
    }
    else{ //Si no esta
        configureFont(flag,&font,true);

        //Si el cursor tiene un texto seleccionado
        if(cursor.hasSelection()){
            cursor.setCharFormat(font);
        }
        else{ //si no hay texto seleccionado
            texto=" ";
            cursor.insertText(texto,font);
            cursor.setPosition(cursor.position()-1);
        }
    }
}

///////////////////////////
/// \brief document::changeFont
///Método para el cambio de formato del texto o de un fragmento de el
////////////////////////
void document::changeFont(QString family,int size){
    //Cursor utilizado para realizar el cambio de formato
    QTextCursor cursor(textPanel->textCursor());

    QTextCharFormat font(cursor.charFormat());
    font.setFontFamily(family);
    font.setFontPointSize(size);

    //Si el cursor tiene un texto seleccionado
    if(cursor.hasSelection()){
        cursor.setCharFormat(font);
    }
    else{ //si no hay texto seleccionado
        QString texto(" ");
        cursor.insertText(texto,font);
        cursor.setPosition(cursor.position()-1);
    }

}

////////////////////////////////
/// \brief document::changeAlign
/// Método para el cambio de alineamiento del texto
////////////////////////////////
void document::changeAlign(AlignFlag flag){
    //Cursor utilizado para realizar el cambio de formato
    QTextCursor cursor(textPanel->textCursor());
    bool isTable=false;

    /*if(cursor.charFormat().isTableFormat()){
       QTextTableFormat format(cursor.charFormat().toTableFormat());
       isTable=true;
       switch(flag){
           case AlignFlag::leftAlign:
                format.setAlignment(Qt::AlignLeft);
           break;
           case AlignFlag::centerAlign:
               format.setAlignment(Qt::AlignCenter);
           break;
           case AlignFlag::rightAlign:
               format.setAlignment(Qt::AlignRight);
           break;
       }
       cursor.setCharFormat(format.toCharFormat());
    }
    else{*/
        //Creamos el objeto formato a partir del formato que ya tiene el texto
        QTextBlockFormat format(cursor.blockFormat());
        switch(flag){
            case AlignFlag::leftAlign:
                 format.setAlignment(Qt::AlignLeft);
            break;
            case AlignFlag::centerAlign:
                format.setAlignment(Qt::AlignCenter);
            break;
            case AlignFlag::rightAlign:
                format.setAlignment(Qt::AlignRight);
            break;
        }
        cursor.setBlockFormat(format);
    //}

}

///////////////////////////
/// \brief document::print
/// Método para la creación de un pdf a partir
/// del documento actualmente visible
//////////////////////////
void document::print(QString name){

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFileName(pathPdf+"/"+name+".pdf");
    printer.setFullPage(true);
    printer.setOutputFormat(QPrinter::PdfFormat);
    textPanel->print(&printer);
    printer.newPage();

}

//////////////////
/// \brief insertTable
/// Método para insertar una tabla en nuestro documento actualmente visible
///////////////////
void document::insertTable(int rows,int cols,Qt::Alignment flag){
    if(rows>0 && cols>0){
        //Cursor utilizado para realizar la insercion
        QTextCursor cursor(textPanel->textCursor());

        //Configuramos nuestro table
        QTextTableFormat tableFormat;
        tableFormat.setAlignment(flag);
        tableFormat.setBorder(0.5);
        tableFormat.setCellPadding(10);
        tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Double);
        //tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 40));

        //Insertamos la table
        cursor.insertTable(rows,cols,tableFormat);
    }
}

//////////////////
/// \brief insertImage
/// Método para insertar una tabla en nuestro documento actualmente visible
///////////////////
void document::insertImage(QString imagePath,int width,int height){
        //Cursor utilizado para realizar la insercion
        QTextCursor cursor(textPanel->textCursor());

        //Configuramos nuestro imagen
        QTextImageFormat ImageFormat;
        ImageFormat.setHeight(height);
        ImageFormat.setWidth(width);
        ImageFormat.setName(imagePath);

        //Insertamos la Imagen
        cursor.insertImage(ImageFormat);
}

///
/// \brief document::isOpenFile
/// \return
///
bool document::isOpenFile(){
    return isOpen;
}

///
/// \brief document::isSearchFile
/// \return
///
bool document::isSearchFile(){
    return isSearch;
}

///
/// \brief document::isEmpty
/// \return
///
bool document::isEmpty(){
    bool salida=false;
    QString texto=textPanel->toPlainText();
    if(texto.size()==0){
        salida=true;
    }

    return salida;
}

/////////
/// \brief document::isImage
/// \return
////////
bool document::isImage(){
    bool salida=false;
    QTextCursor cursor(textPanel->textCursor());

    //Cursor para checkear correctamente el formato actual del texto
    QTextCursor checkCursor(textPanel->textCursor());

    //Cambiamos la posición de este cursor auxiliar para las comprobaciones de formato
    checkCursor.setPosition(cursor.selectionStart()+1,QTextCursor::MoveAnchor);
    checkCursor.setPosition(cursor.selectionEnd(),QTextCursor::KeepAnchor);

    if(checkCursor.charFormat().isImageFormat() && cursor.hasSelection()){
        salida=true;
    }
    return salida;
}

///
/// \brief document::getName
/// \return
///
QString document::getName(){
    return fileName;
}

///////////////////////
/// \brief document::getPath
/// \return
///////////////////////
QString document::getPath(){
    return path;
}

///////////////////////
/// \brief document::getTextPanel
/// \return
///////////////////////
QTextEdit* document::getTextPanel(){
    return textPanel;
}

///////////////////////
/// \brief document::setPath
/// \param entrada
///////////////////////
void document::setPath(QString entrada){
    path=entrada;
}

/////////////////////
/// \brief document::getSizeImage
/// \return
////////////////////
std::pair<int,int> document::getSizeImage(){
    std::pair<int,int> salida;

    QTextCursor cursor(textPanel->textCursor());

    //Cursor para checkear correctamente el formato actual del texto
    QTextCursor checkCursor(textPanel->textCursor());

    //Cambiamos la posición de este cursor auxiliar para las comprobaciones de formato
    checkCursor.setPosition(cursor.selectionStart()+1,QTextCursor::MoveAnchor);
    checkCursor.setPosition(cursor.selectionEnd(),QTextCursor::KeepAnchor);

    QTextImageFormat format=checkCursor.charFormat().toImageFormat();
    salida.second=format.height();
    salida.first=format.width();

    return salida;

}

///////////////////////
/// \brief document::setName
/// \param entrada
///////////////////////
void document::setName(QString entrada){
    fileName=entrada;
}

///////////////////////
/// \brief document::setPathPdf
/// \param entrada
/////////////////////
void document::setPathPdf(QString entrada){
    pathPdf=entrada;
}
///
/// \brief setSizeImage
///
void document::setSizeImage(int height,int width){
    QTextCursor cursor(textPanel->textCursor());

    QTextImageFormat format=cursor.charFormat().toImageFormat();
    format.setHeight(height);
    format.setWidth(width);

    cursor.setCharFormat(format);
}


void document::desactiveSearch(){
    QString texto=textPanel->toHtml();

    //Realizamos el reemplazo
    texto.replace("background-color:#ffff00;","");
    textPanel->setHtml(texto);
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

////////////////////////////////
/// \brief document::configureFont
/// Método para configurar internamente el formato del texto
/////////////////////////
void document::configureFont(FormatFlag flag,QTextCharFormat *font,bool value){

     switch(flag){
        case FormatFlag::bold : //Caso -> texto negrita
             if(value)font->setFontWeight(QFont::Bold);
             else font->setFontWeight(QFont::Normal);
             break;
        case FormatFlag::italic : //Caso -> texto cursiva
             font->setFontItalic(value);
             break;
        case FormatFlag::underline :  //Caso -> texto subrayado
             font->setFontUnderline(value);
             break;

     }
}


///////////////////////////////////
/// \brief document::detectformat
/// Método para detectar en que formato esta el codigo
///////////////////////////////////
bool document::detectFormat(FormatFlag flag,QTextCursor *cursor){
    bool salida=false;
    switch(flag){
       case FormatFlag::bold : //Caso -> texto negrita
            salida=cursor->charFormat().font().bold();
            break;
       case FormatFlag::italic : //Caso -> texto cursiva
            salida=cursor->charFormat().font().italic();
            break;
       case FormatFlag::underline : //Caso -> texto subrayado
            salida=cursor->charFormat().font().underline();
            break;
    }
    return salida;
}
