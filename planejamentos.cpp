#include "planejamentos.h"
#include "ui_planejamentos.h"

Planejamentos::Planejamentos(QWidget *parent) :QDialog(parent), ui(new Ui::Planejamentos) {
    ui->setupUi(this);
}

Planejamentos::~Planejamentos(){
    delete ui;
}

void Planejamentos::on_le_newCat_selectionChanged(){
    ui->le_newCat->clear();
}

