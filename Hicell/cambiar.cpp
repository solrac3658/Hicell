#include "cambiar.h"
#include "ui_cambiar.h"
#include <venta.h>
#include <ingresos.h>
#include <egreso.h>
#include <inventario.h>
#include <modificar.h>
#include <alertainventario.h>
#include <clave.h>
#include <agregar.h>
#include <QSqlQuery>
#include <QCryptographicHash>





Cambiar::Cambiar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Cambiar)
{
    ui->setupUi(this);


    /**********************************************Creacion Base de Datos**********************************/

       mydb=QSqlDatabase::addDatabase("QSQLITE");
       mydb.setDatabaseName("hicelldb.sqlite");

       if (!mydb.open()){
            msgBox.setText("No se Pudo conectar con la base de Datos");
            msgBox.exec();
       }

    /******************************************Fin Creacion Base de Datos**********************************/
    connect(ui->actionActualizar,&QAction::triggered,this,&Cambiar::mostrarActualizar);
    connect(ui->actionContabilidad,&QAction::triggered,this,&Cambiar::mostrarIngreso);
    connect(ui->actionEgresos,&QAction::triggered,this,&Cambiar::mostrarEgreso);
    connect(ui->actionInventario,&QAction::triggered,this,&Cambiar::mostrarInventario);
    connect(ui->actionDetalle,&QAction::triggered,this,&Cambiar::mostrarModificar);
    connect(ui->actionVenta,&QAction::triggered,this, &Cambiar::mostrarVenta);
    connect(ui->actionAlertas,&QAction::triggered,this,&Cambiar::mostrarAlerta);
}

Cambiar::~Cambiar()
{
    delete ui;
}

void Cambiar::mostrarActualizar() {

    Clave cl;
    cl.setModal(true);
    cl.exec();
    int result = cl.result();
    if (result==1){
    mydb.close();
    Agregar *agregar = new Agregar();
    this->destroy();
    agregar->show();
    }
}


void Cambiar::mostrarIngreso() {

    Clave cl;
    cl.setModal(true);
    cl.exec();
    int result = cl.result();
    if (result==1){
    mydb.close();
    Ingresos *ingreso = new Ingresos();
    this->destroy();
    ingreso->show();
    }
}

void Cambiar::mostrarEgreso() {

    mydb.close();
    Egreso *egreso = new Egreso();
    this->destroy();
    egreso->show();
}

void Cambiar::mostrarInventario(){


    mydb.close();
    inventario *Inventario = new inventario();
    this->destroy();
    Inventario->show();

}

void Cambiar::mostrarModificar() {


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

void Cambiar::mostrarVenta() {

        mydb.close();
        Venta *venta = new Venta();
        this->destroy();
        venta->show();


}

void Cambiar::mostrarAlerta() {

    mydb.close();
    AlertaInventario *alerta = new AlertaInventario();
    this->destroy();
    alerta->show();
}

void Cambiar::on_pushButton_guardar_clicked()
{

    QString nueva, repetir;
    QSqlQuery query;
    QString verificar = ui->lineEdit_cUuario->text();
    repetir = QString(QCryptographicHash::hash((ui->lineEdit_2->text().toLocal8Bit()),QCryptographicHash::Md5).toHex());
    nueva = QString(QCryptographicHash::hash((ui->lineEdit_cUuario->text().toLocal8Bit()),QCryptographicHash::Md5).toHex());
    verificar.replace(" ","");

    if (verificar != ""){
    if (nueva != repetir){

        msgBox.setText("Las Contraseñas deben ser Iguales");
        msgBox.exec();
    } else {
        query.prepare("update usuario set clave = '"+nueva+"' where idUsuario = 'master'");
         if (!query.exec()){
             msgBox.setText("Hubo un Problema al Actualizar");
             msgBox.exec();
         }else {
             msgBox.setText("Se ha Actualizado la Contraseña");
             msgBox.exec();
             mostrarVenta();
            }

   }
    }


}

void Cambiar::on_pushButton_cancelar_clicked()
{
   mostrarVenta();
}
