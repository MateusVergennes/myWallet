#ifndef MYWALLET_H
#define MYWALLET_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtSql>
#include <QFileInfo>//torna o banco de dados acessivel ao usuario,faz um backup do arquivo de recursos para um diretorio que o usuario acessa
#include <QDebug>
#include <QColor>
#include <QBrush>
#include "add_data.h"

QT_BEGIN_NAMESPACE
namespace Ui { class myWallet; }
QT_END_NAMESPACE

class myWallet : public QMainWindow
{
    Q_OBJECT

public:
    myWallet(QWidget *parent = nullptr);

    void start();
    //QString user = home + "/.config/mytodo.db";
    QString user = QCoreApplication::applicationDirPath() + "/myWallet.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    void listViewDados();

    ~myWallet();

private slots:
    void on_actionSair_triggered();

    void on_actionSobre_N_s_triggered();

    void on_pushButton_clicked();

private:
    Ui::myWallet *ui;
};
#endif // MYWALLET_H
