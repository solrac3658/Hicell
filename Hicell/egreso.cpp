#include "egreso.h"
#include "ui_egreso.h"
#include <venta.h>
#include <ingresos.h>
#include <agregar.h>
#include <modificar.h>
#include <inventario.h>
#include <cambiar.h>
#include <clave.h>
#include <alertainventario.h>
#include <QDateTime>

Egreso::Egreso(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Egreso)
{
    ui->setupUi(this);
    QDateTime UTC(QDateTime::currentDateTimeUtc());
    QDateTime local(UTC.toLocalTime());
    QString fecha = local.toString("yyyy-MM-dd");
    ui->dateEdit_eFecha->setDate(QDate::currentDate());

    /********************************** Validadores de tipo *******************************************************/

     ui->lineEdit_eValor->setValidator( new QDoubleValidator(0, 9999999, 2, this) );

    /******************************** Validadores de tipo *********************************************************/


    /**********************************************Creacion Base de Datos**********************************/

       mydb=QSqlDatabase::addDatabase("QSQLITE");
       mydb.setDatabaseName("hicelldb.sqlite");

       if (!mydb.open()){
            msgBox.setText("No se Pudo conectar con la base de Datos");
            msgBox.exec();
       }

    /******************************************Fin Creacion Base de Datos**********************************/

       connect(ui->actionActualizar,&QAction::triggered,this,&Egreso::mostrarAgregar);
       connect(ui->actionContabilidad,&QAction::triggered,this,&Egreso::mostrarIngreso);
       connect(ui->actionVenta,&QAction::triggered,this,&Egreso::mostrarVenta);
       connect(ui->actionInventario,&QAction::triggered,this,&Egreso::mostrarInventario);
       connect(ui->actionDetalle,&QAction::triggered,this,&Egreso::mostrarModificar);
       connect(ui->actionCambio,&QAction::triggered,this,&Egreso::mostrarCambiar);
       connect(ui->actionAlertas,&QAction::triggered,this,&Egreso::mostrarAlerta);
}

Egreso::~Egreso()
{
    delete ui;
}


void Egreso::mostrarVenta(){

    Venta *venta = new Venta();
    this->destroy();
    venta->show();
}

void Egreso:: mostrarAgregar(){

    Clave cl;
    cl.setModal(true);
    cl.exec();
    int result = cl.result();
    if (result==1){
    Ingresos *ingresos = new Ingresos();
    this->destroy();
    ingresos->show();
    }
}

void Egreso:: mostrarIngreso(){

    Clave cl;
    cl.setModal(true);
    cl.exec();
    int result = cl.result();
    if (result==1){
    Ingresos *ingresos = new Ingresos();
    this->destroy();
    ingresos->show();
    }
}

void Egreso::mostrarInventario(){

    mydb.close();
    inventario *Inventario = new inventario();
    this->destroy();
    Inventario->show();

}

void Egreso::mostrarModificar() {

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

void Egreso::mostrarCambiar() {


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

void Egreso::mostrarAlerta() {

    mydb.close();
    AlertaInventario *alerta = new AlertaInventario();
    this->destroy();
    alerta->show();
}



void Egreso::on_pushButton_eGuardar_clicked()
{
    QSqlQuery query; 
    QDate fechaF = ui->dateEdit_eFecha->date();
    QString fecha = fechaF.toString("dd-MM-yyyy");
    QString tipo = ui->comboBox_eTipo->currentText();
    QString formaPago = ui->comboBox_eFormapago->currentText();
    QString descripcion = ui->lineEdit_eDescripcion->text();
    QString valor = ui->lineEdit_eValor->text();

    if(fecha.length()<=0 || descripcion.length()<=0 || valor.toFloat()<=0){
        msgBox.setText("Datos Invalidos!!");
        msgBox.exec();
    }else {

        query.prepare("INSERT INTO egreso (fecha, descripcion, tipo, formaPago, valor) " "VALUES (:fecha, :descripcion, :tipo, :formaPago, :valor)");
        query.bindValue(":fecha",fecha);
        query.bindValue(":descripcion",descripcion);
        query.bindValue(":tipo",tipo);
        query.bindValue(":formaPago", formaPago);
        query.bindValue(":valor", valor.toFloat());

        if (!query.exec()){
            // qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

             msgBox.setText("Ocurrio un Error Almacenando el" + tipo);
             msgBox.exec();
        }else {
             msgBox.setText("El " + tipo + " se almacenado exitosamente!!");
             msgBox.exec();
             ui->dateEdit_eFecha->setDate(QDate::currentDate());
             ui->lineEdit_eValor->clear();
             ui->lineEdit_eDescripcion->clear();
             ui->comboBox_eTipo->setCurrentIndex(0);
             ui->comboBox_eFormapago->setCurrentIndex(0);



        }
    }
}


