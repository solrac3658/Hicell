#include "crearusuario.h"
#include "ui_crearusuario.h"

CrearUsuario::CrearUsuario(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CrearUsuario)
{
    ui->setupUi(this);
}

CrearUsuario::~CrearUsuario()
{
    delete ui;
}
