#include "editar.h"
#include "ui_editar.h"

Editar::Editar(QWidget *parent, int id, QString description, QString typeTable) : QDialog(parent), ui(new Ui::Editar){
    ui->setupUi(this);

    ui->label->setText(QString::number(id) );
    ui->lineEdit->setText(description);
    ui->label_2->setText(typeTable);
}

Editar::~Editar(){
    delete ui;
}

void Editar::on_pushButton_clicked(){
    QString id = ui->label->text();
    QString typeTable = ui->label_2->text();
    QString id_name = typeTable;
    id_name.chop(1);//para retirar o "s" do tipo de id, que é ou expense_id ou income_id, já que o dado chega como expenses/incomes
    id_name += "_id";

    QSqlQuery query;
    QString sql = "DELETE FROM " + typeTable + "  WHERE " + id_name + "=" + id;
    qDebug() << sql;
    query.prepare(sql);

    if(query.exec()){
        close();
    }else{
        qDebug() << "Falha ao Deletar a Tarefa.";
    }
}

