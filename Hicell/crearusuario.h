#ifndef CREARUSUARIO_H
#define CREARUSUARIO_H

#include <QMainWindow>

namespace Ui {
class CrearUsuario;
}

class CrearUsuario : public QMainWindow
{
    Q_OBJECT

public:
    explicit CrearUsuario(QWidget *parent = nullptr);
    ~CrearUsuario();

private:
    Ui::CrearUsuario *ui;
};

#endif // CREARUSUARIO_H
