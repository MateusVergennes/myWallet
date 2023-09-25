#ifndef ADD_DATA_H
#define ADD_DATA_H

#include <QDialog>
#include <QMessageBox>
#include <QStringList>
#include <QComboBox>
#include <QtSql>
#include <QFileInfo>
#include <QDebug>
#include "mywallet.h"

namespace Ui {
class Add_data;
}

class Add_data : public QDialog
{
    Q_OBJECT

public:
    explicit Add_data(QWidget *parent = nullptr);
    void comboBoxControl();
    int db_takeIdCategory();
    ~Add_data();

private slots:
    void on_pb_add_clicked();

private:
    Ui::Add_data *ui;
};

#endif // ADD_DATA_H
