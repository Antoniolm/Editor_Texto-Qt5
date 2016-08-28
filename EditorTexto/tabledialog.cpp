//////////////////////////////////////////
///
///@author Antonio David López Machado
///
/////////////////////////////////////////

#include "tabledialog.h"
#include "ui_tabledialog.h"
#include <document.h>

TableDialog::TableDialog(document *docu): QDialog(0)
{
    //Realizamos la configuración inicial
    ui=new Ui::TableDialog;
    ui->setupUi(this);
    doc=docu;
    setWindowTitle("Format Table");
}

TableDialog::~TableDialog(){
    delete ui;

}

///////////////////
/// \brief TableDialog::on_createTable_clicked
///Método para obtener el formato de nuestra nueva tabla
///////////////////
void TableDialog::on_createTable_clicked()
{
    Qt::Alignment flag;
    QString align=ui->AlignList->currentText();

    //Comprobamos la alineación seleccionada y obtenemos
    //la flag necesaria para el formato
    if(align=="Left")flag=Qt::AlignLeft;
    if(align=="Center")flag=Qt::AlignCenter;
    if(align=="Right")flag=Qt::AlignRight;

    //Lanzamos el método para la creación de la tabla
    doc->insertTable(ui->rows->value(),ui->columns->value(),flag);

    //Cerramos la interfaz
    close();
}
