#include "mywallet.h"
#include "ui_mywallet.h"

myWallet::myWallet(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::myWallet)
{
    ui->setupUi(this);
}

myWallet::~myWallet()
{
    delete ui;
}


void myWallet::on_actionSair_triggered(){
    close();
}


void myWallet::on_actionSobre_N_s_triggered(){
    QMessageBox::about(this, "Sobre Esse Projeto", "<h2>myWallet 1.0.0</h2>"
                                                   "<p>Desenvolvido por Mateus Vergennes <br>"
                                                   "Projeto de Carteira p/ Controle Financeiro de Qt com C++<br>"
                                                   "Copyright 2008-2023 Matt Systems Inc. </p>");
}

