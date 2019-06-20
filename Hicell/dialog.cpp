#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_crear_clicked()
{
    this->accept();
}

void Dialog::on_pushButton_cancelar_clicked()
{
     this->reject();
}
