#ifndef EDITAR_H
#define EDITAR_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class Editar;
}

class Editar : public QDialog
{
    Q_OBJECT

public:
    explicit Editar(QWidget *parent = nullptr, int id = 0, QString description = NULL, QString typeTable = NULL, QString valor = NULL, QString categoria = NULL);
    void comboBoxControl();
    int db_takeIdCategory();
    ~Editar();

private slots:
    void on_pushButton_clicked();

    void on_pb_Editar_clicked();

private:
    Ui::Editar *ui;
    int id_table = 0;
};

#endif // EDITAR_H
