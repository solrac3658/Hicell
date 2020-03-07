#ifndef EGRESO_H
#define EGRESO_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>



namespace Ui {
class Egreso;
}

class Egreso : public QMainWindow
{
    Q_OBJECT

public:
    explicit Egreso(QWidget *parent = nullptr);
    ~Egreso();

private slots:


    void on_pushButton_eGuardar_clicked();

    void mostrarVenta();
    void mostrarIngreso();
    void mostrarAgregar();
    void mostrarInventario();
    void mostrarModificar();
    void mostrarCambiar();
    void mostrarAlerta();

private:
    Ui::Egreso *ui;
    QSqlDatabase mydb;
    QMessageBox msgBox;
};

#endif // EGRESO_H
