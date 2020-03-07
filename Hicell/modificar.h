#ifndef MODIFICAR_H
#define MODIFICAR_H
#include <QtSql>
#include <QMessageBox>
#include <QMainWindow>
#include <QTableWidgetItem>

namespace Ui {
class Modificar;
}

class Modificar : public QMainWindow
{
    Q_OBJECT

public:
    explicit Modificar(QWidget *parent = nullptr);
    ~Modificar();

private slots:


    void mostrarActualizar();
    void mostrarIngreso();
    void mostrarEgreso();
    void mostrarInventario();
    void mostrarVenta();
    void mostrarCambiar();
    void mostrarAlerta();

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_tableWidget_cellDoubleClicked(int row, int column);


    void on_lineEdit_mDescuento_textEdited(const QString &arg1);


    void on_tableWidget_2_itemSelectionChanged();

    void on_pushButton_mGuardar_clicked();

    void on_lineEdit_mEfectivo_textEdited(const QString &arg1);

    void on_lineEdit_mRedCompra_textEdited(const QString &arg1);

private:
    Ui::Modificar *ui;
    QSqlDatabase mydb;
    QMessageBox msgBox;
    float total;
    float descuento, efectivo, redcompra;
    QString idIngreso;
    int* idDetalle;
};

#endif // MODIFICAR_H
