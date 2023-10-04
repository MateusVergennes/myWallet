#ifndef PLANEJAMENTOS_H
#define PLANEJAMENTOS_H

#include <QDialog>
#include <QComboBox>
#include <QtSql>
#include <QFileInfo>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class Planejamentos;
}

class Planejamentos : public QDialog
{
    Q_OBJECT

public:
    explicit Planejamentos(QWidget *parent = nullptr);
    void comboBoxControl();
    ~Planejamentos();

private slots:

    void on_pb_addCat_clicked();

    void on_cb_CatExists_currentTextChanged(const QString &arg1);

    void on_pb_deleteCat_clicked();

    void on_pb_editCat_clicked();

private:
    Ui::Planejamentos *ui;
};

#endif // PLANEJAMENTOS_H
