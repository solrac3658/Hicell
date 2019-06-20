#include "clave.h"
#include "ui_clave.h"
#include <QSqlQuery>
#include <QCryptographicHash>

Clave::Clave(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Clave)
{
    ui->setupUi(this);

    /**********************************************Creacion Base de Datos**********************************/

       mydbaux=QSqlDatabase::addDatabase("QSQLITE");
       mydbaux.setDatabaseName("hicelldb.sqlite");

       if (!mydbaux.open()){
            msgBox.setText("No se Pudo conectar con la base de Datos");
            msgBox.exec();
       }

    /******************************************Fin Creacion Base de Datos**********************************/
}

Clave::~Clave()
{
    delete ui;
}

void Clave::on_pushButton_clicked()
{
    QString clave, usuario;
   clave = QString(QCryptographicHash::hash((ui->lineEdit_2->text().toLocal8Bit()),QCryptographicHash::Md5).toHex());
    usuario = ui->lineEdit_cUuario->text();
    QSqlQuery query;
    query.prepare("select idUsuario from usuario where idUsuario ='"+usuario+"' and clave = '"+clave+"' ");
    if (!query.exec()){
        msgBox.setText("Ocurrio un problema con la busqueda");
        msgBox.exec();
    }
    if(query.next()){
        mydbaux.close();
        this->accept();

    }else {
        msgBox.setText("Usuario o Contraseña Incorrecta");
        msgBox.exec();
        }

}

void Clave::on_pushButton_2_clicked()
{
    this->reject();
}
