#include "formapago.h"
#include "ui_formapago.h"
#include <QSqlQuery>
#include <QDateTime>

formapago::formapago(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formapago)
{
    ui->setupUi(this);

    ui->lineEdit_descuento->setValidator( new QDoubleValidator(0, 9999999, 2, this) );
    ui->lineEdit_efectivo->setValidator( new QDoubleValidator(0, 9999999, 2, this) );
    ui->lineEdit_redCompra->setValidator( new QDoubleValidator(0, 9999999, 2, this) );



    /**********************************************Creacion Base de Datos**********************************/

       mydbaux=QSqlDatabase::addDatabase("QSQLITE");
       mydbaux.setDatabaseName("hicelldb.sqlite");

       if (!mydbaux.open()){
            msgBox.setText("No se Pudo conectar con la base de Datos");
            msgBox.exec();
       }

    /******************************************Fin Creacion Base de Datos**********************************/

}

formapago::~formapago()
{
    delete ui;
}


void formapago::on_pushButton_fpCancelar_clicked()
{
    this->reject();
}

void formapago::passTotal(const QString &path)
{
    Stotal = path;
    total = Stotal.toFloat();
    restante = total;
    ui->lineEdit_total->setText(Stotal);
    ui->lineEdit_restante->setText(QString::number(restante));
}

void formapago::on_lineEdit_descuento_textEdited(const QString &arg1)
{
    float descuentoaux = arg1.toFloat();
    if(descuentoaux + redcompra + efectivo>total){
        msgBox.setText("No puede aplicar un descuento mayor al valor total");
        msgBox.exec();
         ui->lineEdit_descuento->setText(QString::number(descuento));
    }else {
        descuento = descuentoaux;
         restante = total - efectivo - descuento - redcompra;
        ui->lineEdit_restante->setText(QString::number(restante));
      }
}

void formapago::on_lineEdit_efectivo_textEdited(const QString &arg1)
{
    float efectivoaux = arg1.toFloat();
    if(efectivoaux + redcompra + descuento > total){
        msgBox.setText("El monto en Efectivo excede el valor de la Venta");
        msgBox.exec();
        ui->lineEdit_efectivo->setText(QString::number(efectivo));
    }else {
        efectivo = efectivoaux;
        restante = total - efectivo - descuento - redcompra;
        ui->lineEdit_restante->setText(QString::number(restante));
      }
}



void formapago::on_lineEdit_redCompra_textEdited(const QString &arg1)
{
    float redcompraaux = arg1.toFloat();
    if(efectivo + redcompraaux + descuento > total){
        ui->lineEdit_redCompra->setText(QString::number(redcompra));
        msgBox.setText("El monto en RedCompra excede el valor de la Venta");
        msgBox.exec();
    }else {
        redcompra = redcompraaux;
        restante = total - efectivo - descuento - redcompra;
        ui->lineEdit_restante->setText(QString::number(restante));
      }
}

void formapago::on_pushButton_fpguardar_clicked()
{
    QSqlQuery query;
    QDateTime UTC(QDateTime::currentDateTimeUtc());
    QDateTime local(UTC.toLocalTime());
    QString fecha = local.toString("yyyy-MM-dd");

    if (restante == 0){
        query.prepare("INSERT INTO ingreso (fecha, valorTotal, descuento, efectivo, RedCompra) " "VALUES (:fecha, :valorTotal, :descuento, :efectivo, :RedCompra)");
        query.bindValue(":fecha",fecha);
        query.bindValue(":valorTotal",total);
        query.bindValue(":descuento",descuento);
        query.bindValue(":efectivo", efectivo);
        query.bindValue(":RedCompra", redcompra);
        if (!query.exec()){
             //qDebug() << "SqLite error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();
              msgBox.setText("Ocurrio un Error Almacenando el Producto");
              msgBox.exec();
        }else {
            this->accept();
        }
    } else {
        msgBox.setText("Debe Realizar el pago Completo");
        msgBox.exec();
    }
}
