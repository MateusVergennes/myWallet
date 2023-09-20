#ifndef MYWALLET_H
#define MYWALLET_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class myWallet; }
QT_END_NAMESPACE

class myWallet : public QMainWindow
{
    Q_OBJECT

public:
    myWallet(QWidget *parent = nullptr);
    ~myWallet();

private slots:
    void on_actionSair_triggered();

    void on_actionSobre_N_s_triggered();

private:
    Ui::myWallet *ui;
};
#endif // MYWALLET_H
