#include "eliminar.h"
#include "ui_eliminar.h"

Eliminar::Eliminar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Eliminar)
{
    ui->setupUi(this);
}

Eliminar::~Eliminar()
{
    delete ui;
}

void Eliminar::on_pushButton_Eliminar_clicked()
{
    this->accept();
}

void Eliminar::on_pushButton_2_clicked()
{
      this->reject();
}
