#include "modificar.h"
#include "ui_modificar.h"
#include <venta.h>
#include <ingresos.h>
#include <egreso.h>
#include <inventario.h>
#include <modificar.h>
#include <clave.h>
#include <cambiar.h>
#include <QSqlQuery>

Modificar::Modificar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Modificar)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setColumnWidth(0,80);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,100);
    ui->tableWidget->setColumnWidth(3,95);
    ui->tableWidget->setColumnWidth(4,90);
    QStringList titulos;
    titulos<< "Nu. Venta"<<"Valor Total"<<"Descuento"<<"Efectivo"<< "RedCompra";
    ui->tableWidget->setHorizontalHeaderLabels(titulos);

    ui->tableWidget_2->setColumnCount(4);
    ui->tableWidget_2->setColumnWidth(0,100);
    ui->tableWidget_2->setColumnWidth(1,200);
    ui->tableWidget_2->setColumnWidth(2,70);
    ui->tableWidget_2->setColumnWidth(2,68);
    QStringList titulosB;
    titulosB<< "Código"<<"Descripción"<<"Cantidad"<< "Precio";
    ui->tableWidget_2->setHorizontalHeaderLabels(titulosB);

    ui->lineEdit_mDescuento->setValidator( new QDoubleValidator(0, 99999, 2, this) );

    /**********************************************Creacion Base de Datos**********************************/

       mydb=QSqlDatabase::addDatabase("QSQLITE");
       mydb.setDatabaseName("hicelldb.sqlite");

       if (!mydb.open()){
            msgBox.setText("No se Pudo conectar con la base de Datos");
            msgBox.exec();
       }

    /******************************************Fin Creacion Base de Datos**********************************/



       connect(ui->actionActualizar,&QAction::triggered,this,&Modificar::mostrarActualizar);
       connect(ui->actionContabilidad,&QAction::triggered,this,&Modificar::mostrarIngreso);
       connect(ui->actionEgresos,&QAction::triggered,this,&Modificar::mostrarEgreso);
       connect(ui->actionInventario,&QAction::triggered,this,&Modificar::mostrarInventario);
       connect(ui->actionVenta,&QAction::triggered,this,&Modificar::mostrarVenta);
       connect(ui->actionCambio,&QAction::triggered,this,&Modificar::mostrarCambiar);

       ui->dateEdit->setDate(QDate::currentDate());
}

Modificar::~Modificar()
{
    delete ui;
}



void Modificar::mostrarActualizar() {

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


void Modificar::mostrarIngreso() {

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

void Modificar::mostrarEgreso() {

    mydb.close();
    Egreso *egreso = new Egreso();
    this->destroy();
    egreso->show();
}

void Modificar::mostrarInventario(){

    mydb.close();
    inventario *Inventario = new inventario();
    this->destroy();
    Inventario->show();

}

void Modificar::mostrarVenta() {

    mydb.close();
    Venta *venta = new Venta();
    this->destroy();
    venta->show();
}

void Modificar::mostrarCambiar() {


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




void Modificar::on_dateEdit_userDateChanged(const QDate &date)
{
    ui->tableWidget->setRowCount(0);
    ui->tableWidget_2->setRowCount(0);
    ui->lineEdit_mDescuento->setEnabled(false);
    ui->lineEdit_mDescuento->clear();
    ui->lineEdit_mTotal->clear();
    ui->pushButton_mGuardar->setEnabled(false);
    QSqlQuery query;
    QString fecha = date.toString("yyyy-MM-dd");
    int row;
    query.prepare("select idIngreso,valorTotal, descuento, efectivo , RedCompra from ingreso where fecha ='"+fecha+"'");
    if (!query.exec()){
        msgBox.setText("Ocurrio un problema con la busqueda");
        msgBox.exec();
    }else {

        QString id;
        QString valorTotal;
        QString descuento;
        QString Sefectivo;
        QString Sredcompra;
        int fieldNo1 = query.record().indexOf("idIngreso");
        int fieldNo2 = query.record().indexOf("valorTotal");
        int fieldNo3 = query.record().indexOf("descuento");
        int fieldNo4 = query.record().indexOf("efectivo");
        int fieldNo5 = query.record().indexOf("RedCompra");
        while(query.next()){

            id=query.value(fieldNo1).toString();
            valorTotal=query.value(fieldNo2).toString();
            descuento=query.value(fieldNo3).toString();
            Sefectivo=query.value(fieldNo4).toString();
            Sredcompra=query.value(fieldNo5).toString();
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            row=ui->tableWidget->rowCount()-1;
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(id));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(valorTotal));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(descuento));
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(Sefectivo));
            ui->tableWidget->setItem(row,4,new QTableWidgetItem(Sredcompra));

        }
    }
}

void Modificar::on_tableWidget_cellDoubleClicked(int row, int column)
{
    total = 0;
    descuento =0;
    ui->lineEdit_mDescuento->setEnabled(true);
    ui->lineEdit_mEfectivo->setEnabled(true);
    ui->lineEdit_mRedCompra->setEnabled(true);
    ui->pushButton_mGuardar->setEnabled(true);
     ui->tableWidget_2->setRowCount(0);
     QTableWidgetItem *item;
     item = ui->tableWidget->item(row,0);
     QString idVenta;
     idVenta = item->text();
     idIngreso = idVenta;
     QSqlQuery query;
     int count = 0;

     QTableWidgetItem *icon_item = new QTableWidgetItem;
     QIcon icon("delete.png");
     icon_item->setIcon(icon);
     int roww;
     query.prepare("select detalleVenta.codigo, producto.descripcion, detalleVenta.cantidad, producto.precio, detalleVenta.idDetalle from detalleVenta, producto where detalleVenta.idVenta ='"+idVenta+"' and detalleVenta.codigo= producto.codigo;");
     if (!query.exec()){
         msgBox.setText("Ocurrio un problema con la busqueda");
         msgBox.exec();
     }else {
         query.last();
         query.first();
         idDetalle = new int[query.at()+1];
         QString codigo;
         QString descripcion;
         QString cantidad;
         QString precio;
         int fieldNo1 = query.record().indexOf("detalleVenta.codigo");
         int fieldNo2 = query.record().indexOf("producto.descripcion");
         int fieldNo3 = query.record().indexOf("detalleVenta.cantidad");
         int fieldNo4 = query.record().indexOf("producto.precio");
         int fieldNo5 = query.record().indexOf("detalleVenta.idDetalle");
          do{
              codigo=query.value(fieldNo1).toString();
              descripcion=query.value(fieldNo2).toString();
             cantidad=query.value(fieldNo3).toString();
             precio=query.value(fieldNo4).toString();
             idDetalle[count] = query.value(fieldNo5).toInt();
             ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());
             roww=ui->tableWidget_2->rowCount()-1;
             icon_item->setIcon(icon);
             ui->tableWidget_2->setItem(roww,0,new QTableWidgetItem(codigo));
             ui->tableWidget_2->setItem(roww,1,new QTableWidgetItem(descripcion));
             ui->tableWidget_2->setItem(roww,2,new QTableWidgetItem(cantidad));
             ui->tableWidget_2->setItem(roww,3,new QTableWidgetItem(precio));
             total = total + (cantidad.toInt()*precio.toFloat());
             count ++;
          } while(query.next());
          item = ui->tableWidget->item(row,2);
          ui->lineEdit_mDescuento->setText(item->text());
          descuento = ui->lineEdit_mDescuento->text().toFloat();
          ui->lineEdit_mTotal->setText(QString::number(total-descuento));
          item = ui->tableWidget->item(row,3);
          ui->lineEdit_mEfectivo->setText(item->text());
          efectivo = ui->lineEdit_mEfectivo->text().toFloat();
          item = ui->tableWidget->item(row,4);
          ui->lineEdit_mRedCompra->setText(item->text());
          redcompra = ui->lineEdit_mRedCompra->text().toFloat();
     }
}


void Modificar::on_lineEdit_mDescuento_textEdited(const QString &arg1)
{
    descuento = arg1.toFloat();
    ui->lineEdit_mTotal->setText(QString::number(total-descuento));

}

void Modificar::on_tableWidget_2_itemSelectionChanged()
{
    QTableWidgetItem *item;
    total = 0;
    int cant;
    float preci;
    int count = ui->tableWidget_2->rowCount();
    for (int i = 0; i<count; ++i){

        item = ui->tableWidget_2->item(i,2);
        cant = item->text().toInt();
        item = ui->tableWidget_2->item(i,3);
        preci = item->text().toFloat();
        total = total + (cant * preci);
        ui->lineEdit_mTotal->setText(QString::number(total-descuento));

    }
}

void Modificar::on_pushButton_mGuardar_clicked()
{

    on_tableWidget_2_itemSelectionChanged();
    QSqlQuery query;
    QString cantidad;
    bool error = false;

    if((efectivo + redcompra) == (total - descuento)){
    query.prepare("UPDATE ingreso SET valorTotal = :valorTotal, descuento = :descuento, efectivo = :efectivo, RedCompra = :RedCompra where idIngreso ='"+idIngreso+"'");
    query.bindValue(":valorTotal", total);
    query.bindValue(":descuento", descuento);
    query.bindValue(":efectivo", efectivo);
    query.bindValue(":RedCompra", redcompra);
    if (!query.exec()){
         qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError();
         msgBox.setText("Ocurrio un Error Actualizando el Producto");
         msgBox.exec();
        }else {

            for (int i = 0; i<ui->tableWidget_2->rowCount(); i++){

                cantidad = ui->tableWidget_2->item(i,2)->text();
                query.prepare("UPDATE detalleVenta SET cantidad = :cantidad where idDetalle = :idDetalle");
                query.bindValue(":cantidad", cantidad.toInt());
                query.bindValue(":idDetalle",idDetalle[i]);
                if (!query.exec()){
                     qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError();
                     msgBox.setText("Ocurrio un Error Actualizando el Producto");
                     msgBox.exec();
                     error = true;
                    }
            }
            if (!error){
                msgBox.setText("Se ha Actualizado Exitosamente");
                msgBox.exec();
            }

            ui->tableWidget_2->setRowCount(0);
            ui->lineEdit_mDescuento->setEnabled(false);
            ui->lineEdit_mDescuento->clear();
            ui->lineEdit_mEfectivo->setEnabled(false);
            ui->lineEdit_mEfectivo->clear();
            ui->lineEdit_mRedCompra->setEnabled(false);
            ui->lineEdit_mRedCompra->clear();
            ui->lineEdit_mTotal->clear();
            ui->pushButton_mGuardar->setEnabled(false);

            on_dateEdit_userDateChanged(ui->dateEdit->date());

        }
    } else {
        msgBox.setText("El monto de Efectivo mas RedCompra debe coincidir con el total de la Venta");
        msgBox.exec();
    }

}


void Modificar::on_lineEdit_mEfectivo_textEdited(const QString &arg1)
{
        efectivo = arg1.toFloat();
}


void Modificar::on_lineEdit_mRedCompra_textEdited(const QString &arg1)
{
        redcompra = arg1.toFloat();
}
