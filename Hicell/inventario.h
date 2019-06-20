#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class inventario;
}

class inventario : public QMainWindow
{
    Q_OBJECT

public:
    explicit inventario(QWidget *parent = nullptr);
    ~inventario();

private slots:

    void mostrarVenta();
    void mostrarIngreso();
    void mostrarEgreso();
    void mostrarAgregar();
    void Actualizar();
    void mostrarModificar();
    void mostrarCambiar();

    void on_lineEdit_iCodigo_textEdited(const QString &arg1);

    void on_lineEdit_iDescripcion_textEdited(const QString &arg1);

private:
    Ui::inventario *ui;
    QSqlDatabase mydb;
    QMessageBox msgBox;
    double total = 0;
};

#endif // INVENTARIO_H
