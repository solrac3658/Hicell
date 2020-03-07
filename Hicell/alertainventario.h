#ifndef ALERTAINVENTARIO_H
#define ALERTAINVENTARIO_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class AlertaInventario;
}

class AlertaInventario : public QMainWindow
{
    Q_OBJECT

public:
    explicit AlertaInventario(QWidget *parent = nullptr);
    ~AlertaInventario();



private slots:

    void mostrarVenta();
    void mostrarModificar();
    void mostrarInventario();
    void mostrarAgregar();
    void mostrarIngreso();
    void mostrarEgreso();
    void mostrarCambiar();
    void Alertas();

private:
    Ui::AlertaInventario *ui;
    QSqlDatabase mydb;
    QMessageBox msgBox;
};

#endif // ALERTAINVENTARIO_H
