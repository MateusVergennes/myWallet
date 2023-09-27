#include "editar.h"
#include "ui_editar.h"

Editar::Editar(QWidget *parent, int id, QString description, QString typeTable, QString valor, QString categoria) : QDialog(parent), ui(new Ui::Editar){
    ui->setupUi(this);

    id_table = id;
    ui->te_descricao->setText(description);
    ui->lb_typeTable->setText(typeTable);
    ui->le_valor->setText(valor);
    comboBoxControl();
    ui->cb_categoria->setCurrentText(categoria);

}

void Editar::comboBoxControl(){
    QStringList categoryName;

    QSqlQuery query_category;
    QString sql_category = "SELECT name FROM categories";
    query_category.prepare(sql_category);

    if(query_category.exec()) {
        int i = 0;

        while (query_category.next()) {
            categoryName.insert(i, query_category.value(0).toString());
            i++;
        }

    } else {
        qDebug() << "Erro ao executar a consulta SQL:" << query_category.lastError().text();
    }

    //Adicionar os dados no ComboBox:
    ui->cb_categoria->addItems(categoryName);
}

int Editar::db_takeIdCategory(){
    QSqlQuery query;
    int category_id;
    QString category_name = ui->cb_categoria->currentText();

    query.prepare("SELECT category_id FROM categories WHERE name = :name");
    query.bindValue(":name", category_name);

    if (query.exec() && query.next()) {
        // O registro foi encontrado, você pode acessar o category_id
        category_id = query.value(0).toInt();
        qDebug() << "O category_id para '" << category_name << "' é: " << category_id;
            return category_id;
    } else {
        // O registro não foi encontrado
        qDebug() << "Categoria não encontrada para '" << category_name << "'";
            return 0;
    }
}

Editar::~Editar(){
    delete ui;
}

void Editar::on_pushButton_clicked(){
    QString id = QString::number(id_table);
    QString typeTable = ui->lb_typeTable->text();
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


void Editar::on_pb_Editar_clicked(){
    if(ui->te_descricao->toPlainText() == "" || ui->le_valor->text() == ""){
        QMessageBox::warning(this, "Aviso", "Campo não pode ficar Vazio");
            return;
    }

    QString id = QString::number(id_table);
    QString typeTable = ui->lb_typeTable->text();
    QString valor = ui->le_valor->text();
    int category_id = db_takeIdCategory();

    QString id_name = typeTable;
    id_name.chop(1);//para retirar o "s" do tipo de id, que é ou expense_id ou income_id, já que o dado chega como expenses/incomes
    id_name += "_id";

    QSqlQuery query;
    QString sql = "UPDATE " + typeTable + " SET description ='" + ui->te_descricao->toPlainText() + "' "
                  ", amount = '" + valor + "', category_id = '" + QString::number(category_id) + "' WHERE " +id_name +" = " + id;
    query.prepare(sql);

    if(query.exec()){
            close();
    }else{
            qDebug() << "Falha ao Atualizar os Dados.";
    }
}

