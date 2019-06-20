#ifndef INGRESOS_H
#define INGRESOS_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>



namespace Ui {
class Ingresos;
}

class Ingresos : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ingresos(QWidget *parent = nullptr);
    ~Ingresos();

private slots:


    void on_comboBox_tipo_currentIndexChanged(int index);

    void on_comboBox_iFormapago_currentIndexChanged(int index);
    void mostrarVenta();
    void mostrarActualizar();
    void mostrarEgreso();
    void mostrarInventario();
    void mostrarModificar();
    void mostrarCambiar();

    void on_dateEdit_iDate_userDateChanged(const QDate &date);

private:
    Ui::Ingresos *ui;
    int formaPago;
    QString SformaPago;
    QString tipo;
    QString Sfecha;
    QDate fecha;
    QSqlDatabase mydb;
    QMessageBox msgBox;
    float tIngreso=0;
    float tEgreso=0;
    float tDescuento=0;
    float tEfectivo = 0;
    float tRedCompra = 0;
    void agregarEgreso();
    void agregarIngreso();
    void  agregarGasto();
    float efectivo(int tipo, QString forma);


};

#endif // INGRESOS_H
