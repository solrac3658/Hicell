#ifndef CLAVE_H
#define CLAVE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QMessageBox>

namespace Ui {
class Clave;
}

class Clave : public QDialog
{
    Q_OBJECT

public:
    explicit Clave(QWidget *parent = nullptr);
    ~Clave();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Clave *ui;
    QSqlDatabase mydbaux;
    QMessageBox msgBox;
};

#endif // CLAVE_H
