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

