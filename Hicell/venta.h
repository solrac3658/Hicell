#ifndef VENTA_H
#define VENTA_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlQuery>
#include <agregar.h>
#include <ingresos.h>
#include <egreso.h>

namespace Ui {
class Venta;
}

class Venta : public QMainWindow
{
    Q_OBJECT

public:
    explicit Venta(QWidget *parent = nullptr);
    ~Venta();

private slots:


    void on_pushButton_vAgregar_clicked();



    void on_pushButton_vVender_clicked();

    void on_pushButton_vBuscar_clicked();
    void mostrarActualizar();
    void mostrarIngreso();
    void mostrarEgreso();
    void mostrarInventario();
    void mostrarModificar();
    void mostrarCambiar();


    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    Ui::Venta *ui;
    QSqlDatabase mydb;
    QMessageBox msgBox;
    QString formadePago;
    QString descripcion;
    QString Sprecio;
    QString Scantidad;
    QString tipo;
    QString texto;
    float total =0;
    void guardarPago();   


    QAction * act;
};

#endif // VENTA_H
