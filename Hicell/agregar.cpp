#include "agregar.h"
#include "ui_agregar.h"
#include <venta.h>
#include <ingresos.h>
#include <egreso.h>
#include <inventario.h>
#include <modificar.h>
#include <clave.h>
#include <cambiar.h>
#include <QSqlQuery>
#include <dialog.h>


Agregar::Agregar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Agregar)
{
    ui->setupUi(this);



  /********************************** Validadores de tipo *******************************************************/

   ui->lineEdit_aPrecio->setValidator( new QDoubleValidator(0, 9999999, 2, this) );
   ui->lineEdit_aCantidad->setValidator( new QIntValidator(0, 999999, this) );

    /******************************** Validadores de tipo *********************************************************/

 /**********************************************Creacion Base de Datos**********************************/

    mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("hicelldb.sqlite");

    if (!mydb.open()){
         msgBox.setText("No se Pudo conectar con la base de Datos");
         msgBox.exec();
    }

 /******************************************Fin Creacion Base de Datos**********************************/

    connect(ui->lineEdit_aCodigo, &QLineEdit::returnPressed, this, &Agregar::on_pushButton_aBuscar_clicked);
    connect(ui->lineEdit_aCantidad, &QLineEdit::returnPressed, this, &Agregar::on_pushButton_aGuardar_clicked);
    connect(ui->actionVenta,&QAction::triggered,this,&Agregar::mostrarVenta);
    connect(ui->actionContabilidad,&QAction::triggered,this,&Agregar::mostrarIngreso);
    connect(ui->actionEgresos,&QAction::triggered,this,&Agregar::mostrarEgreso);
    connect(ui->actionInventario,&QAction::triggered,this,&Agregar::mostrarInventario);
    connect(ui->actionDetalle,&QAction::triggered,this,&Agregar::mostrarModificar);
    connect(ui->actionCambio,&QAction::triggered,this,&Agregar::mostrarCambiar);
}

Agregar::~Agregar()
{
    delete ui;
}

void Agregar::mostrarIngreso() {

    Clave cl;
    cl.setModal(true);
    cl.exec();
    int result = cl.result();
    if (result==1){
    mydb.close();
   Ingresos *ingresos = new Ingresos();
   this->destroy();
   ingresos->show();
    }
}

void Agregar::mostrarEgreso() {

    mydb.close();
   Egreso *egreso = new Egreso();
   this->destroy();
   egreso ->show();
}

void Agregar::mostrarVenta() {

    mydb.close();
    Venta *venta = new Venta();
    this->destroy();
    venta->show();
}

void Agregar::mostrarInventario(){

    mydb.close();
    inventario *Inventario = new inventario();
    this->destroy();
    Inventario->show();

}

void Agregar::mostrarModificar() {

    Clave cl;
    cl.setModal(true);
    cl.exec();
    int result = cl.result();
    if (result==1){
    mydb.close();
    Modificar *modificar = new Modificar();
    this->destroy();
    modificar->show();
    }
}

void Agregar::mostrarCambiar() {


    Clave cl;
    cl.setModal(true);
    cl.exec();
    int result = cl.result();
    if (result==1){
        mydb.close();
        Cambiar *cambiar = new Cambiar();
        this->destroy();
        cambiar->show();
    }

}


void Agregar::on_pushButton_aBuscar_clicked()
{
    QString texto = ui->lineEdit_aCodigo->text();

    if(texto.length()<=0){

        msgBox.setText("Debe agregar un codigo válido");
        msgBox.exec();

    }else {

        QSqlQuery query;
        query.prepare("select * from producto where codigo ='"+texto+"'");

        if(query.exec()){

                int count=0;
                QString descripcion;
                QString precioV;
                QString precioC;
                QString cantidad;
                QString tipo;
                int fieldNo1 = query.record().indexOf("descripcion");
                int fieldNo2 = query.record().indexOf("precio");
                int fieldNo3 = query.record().indexOf("cantidad");
                int fieldNo4 = query.record().indexOf("tipo");
                int fieldNo5 = query.record().indexOf("costo");
                while(query.next()){
                    count++;
                    descripcion=query.value(fieldNo1).toString();
                    precioV=query.value(fieldNo2).toString();
                    cantidad=query.value(fieldNo3).toString();
                    tipo=query.value(fieldNo4).toString();
                     precioC=query.value(fieldNo5).toString();
                }

                if(count ==1){

                     ui->pushButton_aGuardar->setEnabled(true);
                    ui->lineEdit_aDescripcion->setText(descripcion);
                    ui->lineEdit_aDescripcion->setEnabled(true);
                    ui->lineEdit_aPrecio->setText(precioV);
                    ui->lineEdit_aPrecioC->setEnabled(true);
                    ui->lineEdit_aPrecioC->setText(precioC);
                    ui->lineEdit_aPrecio->setEnabled(true);
                    ui->lineEdit_aCantidad->setText(cantidad);
                    ui->lineEdit_aCantidad->setEnabled(true);
                    ui->comboBox_aTipo->setEnabled(true);

                    if(tipo=="Producto"){
                        ui->comboBox_aTipo->setCurrentIndex(0);
                    }else {
                        ui->comboBox_aTipo->setCurrentIndex(1);
                        ui->lineEdit_aCantidad->setEnabled(false);
                    }

                }else {

                    Dialog dg;
                    dg.setModal(true);
                    dg.exec();
                    int result = dg.result();
                    if(result==1) {
                        nuevo = true;
                        ui->lineEdit_aDescripcion->clear();
                        ui->lineEdit_aPrecio->clear();
                        ui->lineEdit_aPrecioC->clear();
                        ui->lineEdit_aCantidad->clear();
                        ui->comboBox_aTipo->setCurrentIndex(0);
                        ui->comboBox_aTipo->setEnabled(true);
                        ui->pushButton_aGuardar->setEnabled(true);
                        ui->lineEdit_aCantidad->setEnabled(true);
                        ui->lineEdit_aPrecio->setEnabled(true);
                        ui->lineEdit_aDescripcion->setEnabled(true);
                        ui->lineEdit_aPrecioC->setEnabled(true);
                    }

                    if(result==0) {

                        ui->lineEdit_aCodigo->clear();
                        ui->lineEdit_aDescripcion->clear();
                        ui->lineEdit_aPrecio->clear();
                        ui->lineEdit_aPrecioC->clear();
                        ui->lineEdit_aCantidad->clear();
                        ui->comboBox_aTipo->setCurrentIndex(0);
                        nuevo = false;
                    }
                }
        }else {

            msgBox.setText("Ocurrio un problema con la busqueda");
            msgBox.exec();

        }
    }
}

void Agregar::on_comboBox_aTipo_currentIndexChanged(int index)
{
    if(index==1){

        ui->lineEdit_aCantidad->setText("0");
        ui->lineEdit_aCantidad->setEnabled(false);
        ui->lineEdit_aPrecioC->setText("0");
        ui->lineEdit_aPrecioC->setEnabled(false);
    } else {
        ui->lineEdit_aCantidad->setEnabled(true);
        ui->lineEdit_aPrecioC->setEnabled(true);
    }
}

void Agregar::on_pushButton_aGuardar_clicked()
{
    QString guardarCodigo = ui->lineEdit_aCodigo->text();
    QString guardarDescripcion = ui->lineEdit_aDescripcion->text();
    QString Precio = ui->lineEdit_aPrecio->text();
    QString PrecioC = ui->lineEdit_aPrecioC->text();
    QString Cantidad = ui->lineEdit_aCantidad->text();
    QString guardarTipo = ui->comboBox_aTipo->currentText();
    QSqlQuery query;
    int guardarCantidad = Cantidad.toInt();
    float guardarPrecio = Precio.toFloat();
    float guardarPrecioC = PrecioC.toFloat();

    if(nuevo){
        query.prepare("INSERT INTO producto (codigo, descripcion, precio, cantidad, tipo, costo) " "VALUES (:codigo, :descripcion, :precio, :cantidad, :tipo, :costo)");
        query.bindValue(":codigo",guardarCodigo);
        query.bindValue(":descripcion",guardarDescripcion);
        query.bindValue(":precio", guardarPrecio);
        query.bindValue(":cantidad", guardarCantidad);
        query.bindValue(":tipo", guardarTipo);
        query.bindValue(":costo", guardarPrecioC);
        if (!query.exec()){
             qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError();
             msgBox.setText("Ocurrio un Error Almacenando el Producto");
             msgBox.exec();
            }else {
            msgBox.setText("El Producto se a Creado Exitosamente!!");
            msgBox.exec();
            }
        nuevo=false;
    }else {
        query.prepare("UPDATE producto SET descripcion = '"+guardarDescripcion+"', precio = :precio, cantidad = :cantidad, tipo = '"+guardarTipo+"', costo = :costo where codigo ='"+guardarCodigo+"'");
        query.bindValue(":precio", guardarPrecio);
        query.bindValue(":cantidad", guardarCantidad);
        query.bindValue(":costo", guardarPrecioC);

        if (!query.exec()){
             qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError();
             msgBox.setText("Ocurrio un Error Actualizando el Producto");
             msgBox.exec();
            }else {
            msgBox.setText("El Producto se Actualizado Exitosamente!!");
            msgBox.exec();
            }
    }
    ui->lineEdit_aCodigo->clear();
    ui->lineEdit_aDescripcion->clear();
    ui->lineEdit_aPrecio->clear();
    ui->lineEdit_aPrecioC->clear();
    ui->lineEdit_aCantidad->clear();
    ui->comboBox_aTipo->setCurrentIndex(0);
    ui->comboBox_aTipo->setEnabled(false);
    ui->pushButton_aGuardar->setEnabled(false);
    ui->lineEdit_aCantidad->setEnabled(false);
    ui->lineEdit_aPrecio->setEnabled(false);
    ui->lineEdit_aPrecioC->setEnabled(false);
    ui->lineEdit_aDescripcion->setEnabled(false);
}
