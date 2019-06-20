#include "ingresos.h"
#include "ui_ingresos.h"
#include <venta.h>
#include <egreso.h>
#include <agregar.h>
#include <modificar.h>
#include <inventario.h>
#include <cambiar.h>
#include <clave.h>
#include <QSqlQuery>

Ingresos::Ingresos(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ingresos)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setColumnWidth(0,100);
    ui->tableWidget->setColumnWidth(1,350);
    ui->tableWidget->setColumnWidth(2,80);
    ui->tableWidget->setColumnWidth(3,100);
    ui->tableWidget->setColumnWidth(4,98);
    QStringList titulos;
    titulos<<"Código"<< "Descripción"<<"Cantidad"<<"Haber"<<"Deber";
    ui->tableWidget->setHorizontalHeaderLabels(titulos);

    /**********************************************Creacion Base de Datos**********************************/

       mydb=QSqlDatabase::addDatabase("QSQLITE");
       mydb.setDatabaseName("hicelldb.sqlite");

       if (!mydb.open()){
            msgBox.setText("No se Pudo conectar con la base de Datos");
            msgBox.exec();
       }

    /******************************************Fin Creacion Base de Datos**********************************/

       connect(ui->actionActualizar,&QAction::triggered,this,&Ingresos::mostrarActualizar);
       connect(ui->actionVenta,&QAction::triggered,this,&Ingresos::mostrarVenta);
       connect(ui->actionEgresos,&QAction::triggered,this,&Ingresos::mostrarEgreso);
       connect(ui->actionInventario,&QAction::triggered,this,&Ingresos::mostrarInventario);
       connect(ui->actionDetalle,&QAction::triggered,this,&Ingresos::mostrarModificar);
       connect(ui->actionCambio,&QAction::triggered,this,&Ingresos::mostrarCambiar);

        ui->dateEdit_iDate->setDate(QDate::currentDate());

}

Ingresos::~Ingresos()
{
    delete ui;
}
void Ingresos::agregarEgreso()
{
    QString descripcion;
    QString codigo;
    QString Svalor;
    QString forma;
    fecha = ui->dateEdit_iDate->date();
    QString SfechaE = fecha.toString("dd-MM-yyyy");
    QSqlQuery query;
    SformaPago = ui->comboBox_iFormapago->currentText();
    int row;
    tipo = ui->comboBox_tipo->currentText();
    if (ui->comboBox_iFormapago->currentIndex()==0){

        query.prepare("select idEgreso, descripcion, valor from egreso where fecha = '"+SfechaE+"' and tipo = 'Egresos';");
        if (!query.exec()){
            msgBox.setText("Ocurrio un problema con la busqueda 1 ");
            msgBox.exec();
            qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();
        }else {

            while(query.next()){
                codigo=query.value(0).toString();
                descripcion=query.value(1).toString();
                Svalor = query.value(2).toString();
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                row=ui->tableWidget->rowCount()-1;
                ui->tableWidget->setItem(row,0,new QTableWidgetItem(codigo));
                ui->tableWidget->setItem(row,1,new QTableWidgetItem(descripcion));
                ui->tableWidget->setItem(row,2,new QTableWidgetItem("1"));
                ui->tableWidget->setItem(row,4,new QTableWidgetItem("-"+Svalor));
            }
            query.prepare("select SUM(valor) from egreso where fecha = '"+SfechaE+"'and formaPago = 'Efectivo'and tipo = 'Egresos'");
            if (!query.exec()){
                   msgBox.setText("Ocurrio un problema con la busqueda 4 ");
                   msgBox.exec();
               }else {
                query.first();
                tEfectivo = tEfectivo - query.value(0).toInt();
            }
            query.prepare("select SUM(valor) from egreso where fecha = '"+SfechaE+"'and formaPago = 'RedCompra'and tipo = 'Egresos'");
            if (!query.exec()){
                   msgBox.setText("Ocurrio un problema con la busqueda 4 ");
                   msgBox.exec();
               }else {
                query.first();
                tRedCompra = tRedCompra - query.value(0).toInt();
            }

        }

    }else{
        query.prepare("select idEgreso, descripcion, valor from egreso where fecha = '"+SfechaE+"' and tipo = 'Egresos' and formaPago = '"+SformaPago+"';");
        if (!query.exec()){
            msgBox.setText("Ocurrio un problema con la busqueda 1 ");
            msgBox.exec();
            qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();
        }else {

            while(query.next()){
                codigo=query.value(0).toString();
                descripcion=query.value(1).toString();
                Svalor = query.value(2).toString();
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                row=ui->tableWidget->rowCount()-1;
                ui->tableWidget->setItem(row,0,new QTableWidgetItem(codigo));
                ui->tableWidget->setItem(row,1,new QTableWidgetItem(descripcion));
                ui->tableWidget->setItem(row,2,new QTableWidgetItem("1"));
                ui->tableWidget->setItem(row,4,new QTableWidgetItem("-"+Svalor));
            }
            if (SformaPago=="Efectivo"){
                query.prepare("select SUM(valor) from egreso where fecha = '"+SfechaE+"'and formaPago = 'Efectivo'and tipo = 'Egresos'");
                if (!query.exec()){
                       msgBox.setText("Ocurrio un problema con la busqueda 4 ");
                       msgBox.exec();
                   }else {
                    query.first();
                    tEfectivo = tEfectivo - query.value(0).toInt();
                }
            }else{
                query.prepare("select SUM(valor) from egreso where fecha = '"+SfechaE+"'and formaPago = 'RedCompra'and tipo = 'Egresos'");
                if (!query.exec()){
                       msgBox.setText("Ocurrio un problema con la busqueda 4 ");
                       msgBox.exec();
                   }else {
                    query.first();
                    tRedCompra = tRedCompra - query.value(0).toInt();
                }
            }
         }
    }

}
void Ingresos::agregarGasto()
{
    QString descripcion;
    QString codigo;
    QString Svalor;
    QString forma;
    fecha = ui->dateEdit_iDate->date();
    QString SfechaE = fecha.toString("dd-MM-yyyy");
    QSqlQuery query;
    SformaPago = ui->comboBox_iFormapago->currentText();
    int row;
    tipo = ui->comboBox_tipo->currentText();
    if (ui->comboBox_iFormapago->currentIndex()==0){

        query.prepare("select idEgreso, descripcion, valor from egreso where fecha = '"+SfechaE+"' and tipo = 'Gastos';");
        if (!query.exec()){
            msgBox.setText("Ocurrio un problema con la busqueda 1 ");
            msgBox.exec();
            qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();
        }else {

            while(query.next()){
                codigo=query.value(0).toString();
                descripcion=query.value(1).toString();
                Svalor = query.value(2).toString();
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                row=ui->tableWidget->rowCount()-1;
                ui->tableWidget->setItem(row,0,new QTableWidgetItem(codigo));
                ui->tableWidget->setItem(row,1,new QTableWidgetItem(descripcion));
                ui->tableWidget->setItem(row,2,new QTableWidgetItem("1"));
                ui->tableWidget->setItem(row,4,new QTableWidgetItem("-"+Svalor));
            }
            query.prepare("select SUM(valor) from egreso where fecha = '"+SfechaE+"'and formaPago = 'Efectivo'and tipo = 'Gastos'");
            if (!query.exec()){
                   msgBox.setText("Ocurrio un problema con la busqueda 4 ");
                   msgBox.exec();
               }else {
                query.first();
                tEfectivo = tEfectivo - query.value(0).toInt();
            }
            query.prepare("select SUM(valor) from egreso where fecha = '"+SfechaE+"'and formaPago = 'RedCompra'and tipo = 'Gastos'");
            if (!query.exec()){
                   msgBox.setText("Ocurrio un problema con la busqueda 4 ");
                   msgBox.exec();
               }else {
                query.first();
                tRedCompra = tRedCompra - query.value(0).toInt();
            }

        }

    }else{
        query.prepare("select idEgreso, descripcion, valor from egreso where fecha = '"+SfechaE+"' and tipo = 'Gastos' and formaPago = '"+SformaPago+"';");
        if (!query.exec()){
            msgBox.setText("Ocurrio un problema con la busqueda 1 ");
            msgBox.exec();
            qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();
        }else {

            while(query.next()){
                codigo=query.value(0).toString();
                descripcion=query.value(1).toString();
                Svalor = query.value(2).toString();
                ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                row=ui->tableWidget->rowCount()-1;
                ui->tableWidget->setItem(row,0,new QTableWidgetItem(codigo));
                ui->tableWidget->setItem(row,1,new QTableWidgetItem(descripcion));
                ui->tableWidget->setItem(row,2,new QTableWidgetItem("1"));
                ui->tableWidget->setItem(row,4,new QTableWidgetItem("-"+Svalor));
            }
            if (SformaPago=="Efectivo"){
                query.prepare("select SUM(valor) from egreso where fecha = '"+SfechaE+"'and formaPago = 'Efectivo'and tipo = 'Gastos'");
                if (!query.exec()){
                       msgBox.setText("Ocurrio un problema con la busqueda 4 ");
                       msgBox.exec();
                   }else {
                    query.first();
                    tEfectivo = tEfectivo - query.value(0).toInt();
                }
            }else{
                query.prepare("select SUM(valor) from egreso where fecha = '"+SfechaE+"'and formaPago = 'RedCompra'and tipo = 'Gastos'");
                if (!query.exec()){
                       msgBox.setText("Ocurrio un problema con la busqueda 4 ");
                       msgBox.exec();
                   }else {
                    query.first();
                    tRedCompra = tRedCompra - query.value(0).toInt();
                }
            }
         }
    }
}

void Ingresos::agregarIngreso()
{
    fecha = ui->dateEdit_iDate->date();
    Sfecha = fecha.toString("yyyy-MM-dd");
    QSqlQuery query;
    QString descripcion;
    QString codigo;
    QString cantidad;
    QString Singreso;
    QString Sdescuento;
    QString forma;
    QString Sprecio;
    //SformaPago = ui->comboBox_iFormapago->currentText();
    //int index = ui->comboBox_iFormapago->currentIndex();

    int row;
        query.prepare("select producto.codigo, producto.descripcion, SUM (detalleVenta.cantidad), producto.precio from detalleVenta, producto, ingreso where detalleVenta.idVenta=ingreso.idIngreso and detalleVenta.codigo = producto.codigo and ingreso.fecha = '"+Sfecha+"' group by producto.codigo;");

   if (!query.exec()){
       msgBox.setText("Ocurrio un problema con la busqueda 1 ");
       msgBox.exec();
       qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();
   }else {
       while(query.next()){
           codigo=query.value(0).toString();
           descripcion=query.value(1).toString();
           cantidad=query.value(2).toString();
           Sprecio =query.value(3).toString();
           ui->tableWidget->insertRow(ui->tableWidget->rowCount());
           row=ui->tableWidget->rowCount()-1;
           ui->tableWidget->setItem(row,0,new QTableWidgetItem(codigo));
           ui->tableWidget->setItem(row,1,new QTableWidgetItem(descripcion));
           ui->tableWidget->setItem(row,2,new QTableWidgetItem(cantidad));
           ui->tableWidget->setItem(row,3,new QTableWidgetItem(QString::number(Sprecio.toFloat()* cantidad.toInt())));
       }
       query.prepare("select SUM(descuento) from ingreso where fecha = '"+Sfecha+"'");
       if (!query.exec()){
              msgBox.setText("Ocurrio un problema con la busqueda 2 ");
              msgBox.exec();
          }else {
           query.first();
           tDescuento = query.value(0).toInt();
       }
       query.prepare("select SUM(efectivo) from ingreso where fecha = '"+Sfecha+"'");
       if (!query.exec()){
              msgBox.setText("Ocurrio un problema con la busqueda 3 ");
              msgBox.exec();
          }else {
           query.first();
           tEfectivo = query.value(0).toInt();
       }
       query.prepare("select SUM(RedCompra) from ingreso where fecha = '"+Sfecha+"'");
       if (!query.exec()){
              msgBox.setText("Ocurrio un problema con la busqueda 4 ");
              msgBox.exec();
          }else {
           query.first();
           tRedCompra = query.value(0).toInt();
       }

    }

}


void Ingresos::mostrarVenta(){
    Venta *venta = new Venta();
    this->destroy();
    venta->show();
}

void Ingresos::mostrarEgreso(){

    Egreso *egreso = new Egreso();
    this->destroy();
    egreso->show();
}

void Ingresos::mostrarActualizar(){

    Clave cl;
    cl.setModal(true);
    cl.exec();
    int result = cl.result();
    if (result==1){
    Agregar *agregar = new Agregar();
    this->destroy();
    agregar->show();
    }
}
void Ingresos::mostrarInventario(){

    mydb.close();
    inventario *Inventario = new inventario();
    this->destroy();
    Inventario->show();

}

void Ingresos::mostrarModificar() {

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

void Ingresos::mostrarCambiar() {


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

void Ingresos::on_comboBox_tipo_currentIndexChanged(int index)
{
    ui->tableWidget->setRowCount(0);
    formaPago = ui->comboBox_iFormapago->currentIndex();
    fecha = ui->dateEdit_iDate->date();
    Sfecha = fecha.toString("yyyy-MM-dd");
    QString SfechaE = fecha.toString("dd-MM-yyyy");
    QSqlQuery query;
    QString descripcion;
    QString codigo;
    QString cantidad;
    QString Singreso;
    QString Sdescuento;
    formaPago=ui->comboBox_iFormapago->currentIndex();
    float balance;
    tIngreso=0;
    tEgreso=0;
    tDescuento=0;
    tEfectivo =0;
    tRedCompra =0;

    if (index == 0){
        ui->comboBox_iFormapago->setEnabled(false);
        agregarIngreso();
        agregarEgreso();
        agregarGasto();
    } else {
        if(index == 1){
            ui->comboBox_iFormapago->setEnabled(false);
            agregarIngreso();
        }else {
            if (index == 2){
                 agregarEgreso();
                 ui->comboBox_iFormapago->setEnabled(true);
            }else{
                if (index== 3){
                    agregarGasto();
                    ui->comboBox_iFormapago->setEnabled(true);
                }else{
                    agregarEgreso();
                    agregarGasto();
                    ui->comboBox_iFormapago->setEnabled(true);
                }
            }
        }
    }
      balance = tEfectivo+tRedCompra;
      ui->lineEdit_iBalance->setText(QString::number(balance));
      ui->lineEdit_iDescuento->setText(QString::number(tDescuento));
      ui->lineEdit_iefectivo->setText(QString::number(tEfectivo));
      ui->lineEdit_iredcompra->setText(QString::number(tRedCompra));
 }



void Ingresos::on_comboBox_iFormapago_currentIndexChanged(int index)
{
    on_comboBox_tipo_currentIndexChanged(ui->comboBox_tipo->currentIndex());
}

void Ingresos::on_dateEdit_iDate_userDateChanged(const QDate &date)
{
    on_comboBox_tipo_currentIndexChanged(ui->comboBox_tipo->currentIndex());
}

float Ingresos::efectivo(int tipo, QString forma){

    float tEfectivoa =0;
    SformaPago = ui->comboBox_iFormapago->currentText();
    fecha = ui->dateEdit_iDate->date();
    Sfecha = fecha.toString("yyyy-MM-dd");
    QString SfechaA = fecha.toString("dd-MM-yyyy");
    QSqlQuery query,querya;
    QString valorI, valorE;
    query.prepare("select SUM(valorTotal) FROM ingreso where fecha = '"+Sfecha+"' and formaPago = '"+forma+"';");
    querya.prepare("select SUM(valor) FROM egreso where fecha = '"+SfechaA+"' and formaPago = '"+forma+"';");

    if (!query.exec()){
        msgBox.setText("Ocurrio un problema con la busqueda");
        msgBox.exec();
    }
    if (!querya.exec()){
                msgBox.setText("Ocurrio un problema con la busqueda");
                msgBox.exec();
            }
    while (query.next()){
        valorI = query.value(0).toString();
    }
    while (querya.next()){
        valorE = querya.value(0).toString();
    }
    if (tipo == 0){
        tEfectivoa = tEfectivoa + valorI.toFloat();
        tEfectivoa = tEfectivoa - valorE.toFloat();
        return tEfectivoa;
    }
    if (tipo == 1){
        tEfectivoa = tEfectivoa + valorI.toFloat();
        return tEfectivoa;
    }
    if (tipo == 2){
        tEfectivoa = tEfectivoa - valorE.toFloat();
        return tEfectivoa;
    }
    if (tipo == 3){
     QString tipo = ui->comboBox_tipo->currentText();
     querya.prepare("select SUM(valor) FROM egreso where fecha = '"+SfechaA+"' and formaPago = '"+forma+"' and tipo = '"+tipo+"';");
     if (!querya.exec()){
                 msgBox.setText("Ocurrio un problema con la busqueda");
                 msgBox.exec();
             }
     while (querya.next()){
         valorE = querya.value(0).toString();
     }
     tEfectivoa = tEfectivoa - valorE.toFloat();
     return tEfectivoa;
    }
}

