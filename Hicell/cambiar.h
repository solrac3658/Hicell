#ifndef CAMBIAR_H
#define CAMBIAR_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class Cambiar;
}

class Cambiar : public QMainWindow
{
    Q_OBJECT

public:
    explicit Cambiar(QWidget *parent = nullptr);
    ~Cambiar();


private slots:
    void on_pushButton_guardar_clicked();
    void mostrarActualizar();
    void mostrarIngreso();
    void mostrarEgreso();
    void mostrarInventario();
    void mostrarModificar();
    void mostrarVenta();
    void mostrarAlerta();

    void on_pushButton_cancelar_clicked();

private:
    Ui::Cambiar *ui;
    QSqlDatabase mydb;
    QMessageBox msgBox;
};

#endif // CAMBIAR_H
