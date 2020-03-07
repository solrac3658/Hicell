#ifndef AGREGAR_H
#define AGREGAR_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>


namespace Ui {
class Agregar;
}

class Agregar : public QMainWindow
{
    Q_OBJECT

public:
    explicit Agregar(QWidget *parent = nullptr);
    ~Agregar();

private slots:




    void on_pushButton_aBuscar_clicked();

    void on_comboBox_aTipo_currentIndexChanged(int index);

    void on_pushButton_aGuardar_clicked();

    void mostrarVenta();
    void mostrarIngreso();
    void mostrarEgreso();
    void mostrarInventario();
    void mostrarModificar();
    void mostrarCambiar();
    void mostrarAlerta();


private:
    Ui::Agregar *ui;
    QSqlDatabase mydb;
    QMessageBox msgBox;
    bool nuevo = false;  

};

#endif // AGREGAR_H
