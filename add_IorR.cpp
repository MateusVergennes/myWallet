#include "add_IorR.h"
#include "ui_add_IorR.h"

Add::Add(QWidget *parent) :QDialog(parent), ui(new Ui::Add){
    ui->setupUi(this);
}

Add::~Add(){
    delete ui;
}
