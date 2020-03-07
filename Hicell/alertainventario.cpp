#include "alertainventario.h"
#include "ui_alertainventario.h"

#include <venta.h>
#include <ingresos.h>
#include <modificar.h>
#include <egreso.h>
#include <agregar.h>
#include <clave.h>
#include <cambiar.h>
#include <inventario.h>

#include <QSqlQuery>

AlertaInventario::AlertaInventario(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AlertaInventario)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setColumnWidth(0,130);
    ui->tableWidget->setColumnWidth(1,198);
    ui->tableWidget->setColumnWidth(2,70);
    QStringList titulos;
    titulos<< "Codigo"<<"Descripcion"<<"Cantidad";
    ui->tableWidget->setHorizontalHeaderLabels(titulos);

    /**********************************************Creacion Base de Datos**********************************/

       mydb=QSqlDatabase::addDatabase("QSQLITE");
       mydb.setDatabaseName("hicelldb.sqlite");

       if (!mydb.open()){
            msgBox.setText("No se Pudo conectar con la base de Datos");
            msgBox.exec();
       }

    /******************************************Fin Creacion Base de Datos**********************************/
       connect(ui->actionVenta,&QAction::triggered,this,&AlertaInventario::mostrarVenta);
       connect(ui->actionContabilidad,&QAction::triggered,this,&AlertaInventario::mostrarIngreso);
       connect(ui->actionEgresos,&QAction::triggered,this,&AlertaInventario::mostrarEgreso);
       connect(ui->actionActualizar,&QAction::triggered,this,&AlertaInventario::mostrarAgregar);
       connect(ui->actionDetalle,&QAction::triggered,this,&AlertaInventario::mostrarModificar);
       connect(ui->actionCambio,&QAction::triggered,this,&AlertaInventario::mostrarCambiar);
       connect(ui->actionInventario,&QAction::triggered,this,&AlertaInventario::mostrarIngreso);
       Alertas();
}

AlertaInventario::~AlertaInventario()
{
    delete ui;
}
void AlertaInventario::mostrarIngreso() {

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

void AlertaInventario::mostrarEgreso() {

   mydb.close();
   Egreso *egreso = new Egreso();
   this->destroy();
   egreso ->show();
}

void AlertaInventario::mostrarVenta() {

    mydb.close();
    Venta *venta = new Venta();
    this->destroy();
    venta->show();
}

void AlertaInventario::mostrarAgregar(){

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

void AlertaInventario::mostrarModificar() {

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

void AlertaInventario::mostrarCambiar() {


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

void AlertaInventario::mostrarInventario(){

    mydb.close();
    inventario *Inventario = new inventario();
    this->destroy();
    Inventario->show();

}


void AlertaInventario::Alertas()
{

    QSqlQuery query;
    QString Sproducto = "Producto";
    QString codigo;
    QString descripcion;
    QString Scantidad;
    int row;

    query.prepare("select codigo, descripcion, cantidad from producto where tipo = '"+Sproducto+"'and cantidad <= alerta");
    if (!query.exec()){
        msgBox.setText("Ocurrio un problema con la busqueda");
        msgBox.exec();
    }else {
         while(query.next()){
            codigo=query.value(0).toString();
            descripcion=query.value(1).toString();
            Scantidad=query.value(2).toString();
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            row=ui->tableWidget->rowCount()-1;
            ui->tableWidget->setItem(row,0,new QTableWidgetItem(codigo));
            ui->tableWidget->setItem(row,1,new QTableWidgetItem(descripcion));
           ui->tableWidget->setItem(row,2,new QTableWidgetItem(Scantidad));
        }
       }
}

