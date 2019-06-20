#ifndef FORMAPAGO_H
#define FORMAPAGO_H
#include <QtSql>
#include <QMessageBox>

#include <QDialog>

namespace Ui {
class formapago;
}

class formapago : public QDialog
{
    Q_OBJECT

public:
    explicit formapago(QWidget *parent = nullptr);
    ~formapago();

    void passTotal(const QString &path);

private slots:

    void on_pushButton_fpCancelar_clicked();

    void on_lineEdit_descuento_textEdited(const QString &arg1);

    void on_lineEdit_efectivo_textEdited(const QString &arg1);

    void on_lineEdit_redCompra_textEdited(const QString &arg1);

    void on_pushButton_fpguardar_clicked();

private:
    Ui::formapago *ui;
    QString Stotal;
    float efectivo = 0, redcompra = 0, descuento=0, total = 0, restante = 0;
    QSqlDatabase mydbaux;
    QMessageBox msgBox;
};

#endif // FORMAPAGO_H
