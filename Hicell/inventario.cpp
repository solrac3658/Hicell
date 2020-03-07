#include "inventario.h"
#include "ui_inventario.h"
#include <venta.h>
#include <ingresos.h>
#include <modificar.h>
#include <egreso.h>
#include <agregar.h>
#include <clave.h>
#include <cambiar.h>
#include <alertainventario.h>
#include <QSqlQuery>

inventario::inventario(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::inventario)
{
    ui->setupUi(this);


    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setColumnWidth(0,130);
    ui->tableWidget->setColumnWidth(1,200);
    ui->tableWidget->setColumnWidth(2,100);
    ui->tableWidget->setColumnWidth(3,70);
    ui->tableWidget->setColumnWidth(4,100);
    QStringList titulos;
    titulos<< "Codigo"<<"Descripcion"<<"Precio Costo"<<"Cantidad"<< "Precio Total";
    ui->tableWidget->setHorizontalHeaderLabels(titulos);

    /**********************************************Creacion Base de Datos**********************************/

       mydb=QSqlDatabase::addDatabase("QSQLITE");
       mydb.setDatabaseName("hicelldb.sqlite");

       if (!mydb.open()){
            msgBox.setText("No se Pudo conectar con la base de Datos");
            msgBox.exec();
       }

    /******************************************Fin Creacion Base de Datos**********************************/

       connect(ui->actionVenta,&QAction::triggered,this,&inventario::mostrarVenta);
       connect(ui->actionContabilidad,&QAction::triggered,this,&inventario::mostrarIngreso);
       connect(ui->actionEgresos,&QAction::triggered,this,&inventario::mostrarEgreso);
       connect(ui->actionActualizar,&QAction::triggered,this,&inventario::mostrarAgregar);
       connect(ui->actionDetalle,&QAction::triggered,this,&inventario::mostrarModificar);
       connect(ui->actionCambio,&QAction::triggered,this,&inventario::mostrarCambiar);
       connect(ui->actionAlertas,&QAction::triggered,this,&inventario::mostrarAlerta);
       Actualizar();
}

inventario::~inventario()
{
    delete ui;
}

void inventario::mostrarIngreso() {

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

void inventario::mostrarEgreso() {

   mydb.close();
   Egreso *egreso = new Egreso();
   this->destroy();
   egreso ->show();
}

void inventario::mostrarVenta() {

    mydb.close();
    Venta *venta = new Venta();
    this->destroy();
    venta->show();
}

void inventario::mostrarAgregar(){

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

void inventario::mostrarModificar() {

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

void inventario::mostrarCambiar() {


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
void inventario::mostrarAlerta() {

    mydb.close();
    AlertaInventario *alerta = new AlertaInventario();
    this->destroy();
    alerta->show();
}


void inventario::Actualizar (){

    QSqlQuery query;
    QString Sproducto = "Producto";
    QString codigo;
    QString descripcion;
    QString Scantidad;
    QString Scosto;
    double costo;
    double valor;
    double cantidad;
    int row;

    query.prepare("select codigo, descripcion, cantidad, costo from producto where tipo = '"+Sproducto+"'");
    if (!query.exec()){
        msgBox.setText("Ocurrio un problema con la busqueda");
        msgBox.exec();
    }else {
        while(query.next()){
            codigo=query.value(0).toString();
            descripcion=query.value(1).toString();
            Scantidad=query.value(2).toString();
            Scosto=query.value(3).toString();
            costo = Scosto.toDouble();
            cantidad =Scantidad.toDouble();
            valor = costo * cantidad;
            total = total + valor;
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            row=ui->tableWidget->rowCount()-1;
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(codigo));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(descripcion));
            ui->tableWidget->setItem(row,2,new QTableWidgetItem(Scosto));
            ui->tableWidget->setItem(row,3,new QTableWidgetItem(Scantidad));
            ui->tableWidget->setItem(row,4,new QTableWidgetItem(QString::number(valor)));
        }
       }
    ui->label_iTotal->setText(QString::number(total,'g', 10));
}

void inventario::on_lineEdit_iCodigo_textEdited(const QString &arg1)
{
    QString verificar;
    QTableWidgetItem *item;
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {

        item = ui->tableWidget->item(i,0);
        verificar = item->text();

        if(verificar.startsWith(arg1)){

        ui->tableWidget->showRow(i);
        }else {

            ui->tableWidget->hideRow(i);
        }

    }
}

void inventario::on_lineEdit_iDescripcion_textEdited(const QString &arg1)
{
    QString verificar;
    QTableWidgetItem *item;
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {

        item = ui->tableWidget->item(i,1);
        verificar = item->text();

        if(verificar.contains(arg1, Qt::CaseInsensitive)){

        ui->tableWidget->showRow(i);
        }else {

            ui->tableWidget->hideRow(i);
        }

    }
}
