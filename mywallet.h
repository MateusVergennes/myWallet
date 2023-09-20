#ifndef MYWALLET_H
#define MYWALLET_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtSql>
#include <QFileInfo>//torna o banco de dados acessivel ao usuario,faz um backup do arquivo de recursos para um diretorio que o usuario acessa
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class myWallet; }
QT_END_NAMESPACE

class myWallet : public QMainWindow
{
    Q_OBJECT

public:
    myWallet(QWidget *parent = nullptr);

    void start();
    QString dir = ":/database/myWalletdb.db";
    //QString user = home + "/.config/mytodo.db";
    QString user = QCoreApplication::applicationDirPath() + "/myWalletdb.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    ~myWallet();

private slots:
    void on_actionSair_triggered();

    void on_actionSobre_N_s_triggered();

private:
    Ui::myWallet *ui;
};
#endif // MYWALLET_H
