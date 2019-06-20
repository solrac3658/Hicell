#include "venta.h"
#include "ui_venta.h"
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <formapago.h>
#include <QDateTime>
#include <eliminar.h>
#include <inventario.h>
#include <modificar.h>
#include <clave.h>
#include <cambiar.h>


Venta::Venta(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Venta)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setColumnWidth(0,125);
    ui->tableWidget->setColumnWidth(1,200);
    ui->tableWidget->setColumnWidth(2,100);
    ui->tableWidget->setColumnWidth(3,70);
    ui->tableWidget->setColumnWidth(4,100);
    ui->tableWidget->setColumnWidth(5,100);
    ui->tableWidget->setColumnWidth(6,80);
    QStringList titulos;
    titulos<< "Codigo"<<"Descripcion"<<"Tipo"<<"Cantidad"<< "Precio Unitario"<<"Precio Total"<<"Eliminar";
    ui->tableWidget->setHorizontalHeaderLabels(titulos);

    /********************************** Validadores de tipo *******************************************************/

    ui->lineEdit_vCantidad->setValidator( new QIntValidator(0, 999999, this) );

    /******************************** Validadores de tipo *********************************************************/

    act = new QAction(this);

    /**********************************************Creacion Base de Datos**********************************/

       mydb=QSqlDatabase::addDatabase("QSQLITE");
       mydb.setDatabaseName("hicelldb.sqlite");

       if (!mydb.open()){
            msgBox.setText("No se Pudo conectar con la base de Datos");
            msgBox.exec();
       }

    /******************************************Fin Creacion Base de Datos**********************************/
       connect(ui->lineEdit_vCodigo, &QLineEdit::returnPressed, this, &Venta::on_pushButton_vBuscar_clicked);
       connect(ui->lineEdit_vCantidad, &QLineEdit::returnPressed, this, &Venta::on_pushButton_vAgregar_clicked);
       connect(ui->actionActualizar,&QAction::triggered,this,&Venta::mostrarActualizar);
       connect(ui->actionContabilidad,&QAction::triggered,this,&Venta::mostrarIngreso);
       connect(ui->actionEgresos,&QAction::triggered,this,&Venta::mostrarEgreso);
       connect(ui->actionInventario,&QAction::triggered,this,&Venta::mostrarInventario);
       connect(ui->actionDetalle,&QAction::triggered,this,&Venta::mostrarModificar);
       connect(ui->actionCambio,&QAction::triggered,this,&Venta::mostrarCambiar);
}

Venta::~Venta()
{
    delete ui;
}


void Venta::guardarPago(){

    QSqlQuery query;
    QString codVenta;
    QString SlocalCodigo;
    QString SlocalCantidad;
    QString localTipo;
    QTableWidgetItem *item;
    int row =ui->tableWidget->rowCount();

            total=0;
            ui->label_vTotal->setNum(total);
            query.prepare("select MAX(idIngreso) from ingreso");
            if (query.exec()){
                 while (query.next()) {
                 codVenta=query.value(0).toString();
                 }
              }

            for (int i = 0; i <row; i++) {
                item=ui->tableWidget->item(i,0);
                SlocalCodigo=item->text();
                item=ui->tableWidget->item(i,3);
                SlocalCantidad= item->text();
                item=ui->tableWidget->item(i,2);
                localTipo= item->text();
                query.prepare("INSERT INTO detalleVenta (idVenta, codigo, cantidad) " "VALUES (:idVenta, :codigo, :cantidad)");
                query.bindValue(":idVenta",codVenta.toInt());
                query.bindValue(":codigo",SlocalCodigo);
                query.bindValue(":cantidad",SlocalCantidad.toInt());
                if (!query.exec()){
                     //qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();
                     msgBox.setText("Ocurrio un Error Realizando la Venta");
                     msgBox.exec();
                    }

            }
                ui->tableWidget->setRowCount(0);
                ui->pushButton_vVender->setEnabled(false);


}

void Venta::mostrarActualizar() {

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


void Venta::mostrarIngreso() {

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

void Venta::mostrarEgreso() {

    mydb.close();
    Egreso *egreso = new Egreso();
    this->destroy();
    egreso->show();
}

void Venta::mostrarInventario(){


    mydb.close();
    inventario *Inventario = new inventario();
    this->destroy();
    Inventario->show();

}

void Venta::mostrarModificar() {


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

void Venta::mostrarCambiar() {


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



void Venta::on_pushButton_vAgregar_clicked()
{

    QString Snumero = ui->lineEdit_vCantidad->text();

    QTableWidgetItem *icon_item = new QTableWidgetItem;
    QIcon icon("delete.png");
    icon_item->setIcon(icon);

    int cantidad;
    int row;
    float precio;
    float precioTotal;
    int numero =Snumero.toInt();
    cantidad=Scantidad.toInt();
    precio=Sprecio.toFloat();
    if((tipo=="Producto")&&(cantidad<numero)){
        msgBox.setText("No Existe tanto Inventario para el Porducto");
        msgBox.exec();
        ui->lineEdit_vCantidad->setText("1");

    } else {
       precioTotal=numero*precio;
       total=total+precioTotal;
       ui->label_vTotal->setNum(total);
       ui->tableWidget->insertRow(ui->tableWidget->rowCount());
       row =  ui->tableWidget->rowCount() -1;
       ui->tableWidget->setItem(row,0,new QTableWidgetItem(texto));
       ui->tableWidget->setItem(row,1,new QTableWidgetItem(descripcion));
       ui->tableWidget->setItem(row,2,new QTableWidgetItem(tipo));
       ui->tableWidget->setItem(row,3,new QTableWidgetItem(Snumero));
       ui->tableWidget->setItem(row,4,new QTableWidgetItem(Sprecio));
       ui->tableWidget->setItem(row,5,new QTableWidgetItem(QString::number(precioTotal)));
       ui->tableWidget->setItem(row,6,icon_item);
       ui->lineEdit_vCodigo->clear();
       ui->lineEdit_vDescripcion->clear();
       ui->lineEdit_vExistencia->clear();
       ui->lineEdit_vCantidad->setText("1");
       ui->pushButton_vAgregar->setEnabled(false);
       ui->pushButton_vVender->setEnabled(true);

   }

}


void Venta::on_pushButton_vVender_clicked()
{
    formapago fp;
    fp.setModal(true);
    fp.passTotal(QString::number(total));
    fp.exec();
    int result = fp.result();
    if(result==1) {
        formadePago = "Efectivo";
        guardarPago();
    }
}

void Venta::on_pushButton_vBuscar_clicked()
{
   int cantidad=0;
   QSqlQuery query;
   texto = ui->lineEdit_vCodigo->text();
   if(texto.length()<=0){

       msgBox.setText("Debe agregar un codigo válido");
       msgBox.exec();

   }else {

       query.prepare("select * from producto where codigo ='"+texto+"'");
       if (query.exec()){

            int fieldNo = query.record().indexOf("cantidad");
            int fieldNo1 = query.record().indexOf("descripcion");
            int fieldNo2 = query.record().indexOf("precio");
            int fieldNo3 = query.record().indexOf("tipo");

            while(query.next()){
                Scantidad=query.value(fieldNo).toString();
                descripcion=query.value(fieldNo1).toString();
                Sprecio=query.value(fieldNo2).toString();
                tipo=query.value(fieldNo3).toString();
                cantidad ++;
            }
            if(cantidad==0){
                msgBox.setText("Prducto Inexistente!!!");
                msgBox.exec();
            }else {
                if (tipo=="Servicio Técnico"){
                    Scantidad="0";
                }
                ui->lineEdit_vDescripcion->setText(descripcion);
                ui->lineEdit_vExistencia->setText(Scantidad);
                ui->lineEdit_vPrecio->setText(Sprecio);
                ui->pushButton_vAgregar->setEnabled(true);
            }


        }else {
           msgBox.setText("Ocurrio un Error al Buscar el Producto");
           msgBox.exec();
          //qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();
        }

   }
}



void Venta::on_tableWidget_cellDoubleClicked(int row, int column)
{
    if (column==6){
        Eliminar dg;
        dg.setModal(true);
        dg.exec();
        int result = dg.result();
        if (result==1){
            QTableWidgetItem *item = ui->tableWidget->item(row,5);
            QString SprecioTotal = item->text();
            float precioTotal = SprecioTotal.toFloat();
            total = total-precioTotal;
            ui->tableWidget->removeRow(row);
            ui->label_vTotal->setNum(total);
            if (ui->tableWidget->rowCount()==0){
                ui->pushButton_vVender->setEnabled(false);

            }
        }

    }
}
