#include "add_data.h"
#include "ui_add_data.h"

Add_data::Add_data(QWidget *parent) : QDialog(parent), ui(new Ui::Add_data){
    ui->setupUi(this);
    comboBoxControl();

}

void Add_data::comboBoxControl(){
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
    ui->comboBox->addItems(categoryName);
}

int Add_data::db_takeIdCategory(){
        QSqlQuery query;
        int category_id;
        QString category_name = ui->comboBox->currentText();

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

Add_data::~Add_data(){
    delete ui;
}

void Add_data::on_pb_add_clicked(){

    if (ui->comboBox->currentIndex() == -1) {
        QMessageBox::critical(nullptr, "Erro", "Nenhuma Categoria foi selecionada.");
        return;
    }

    if(ui->le_valor->text() == ""){
        QMessageBox::warning(this, "Aviso", "Preencha o Campo Valor.");
        return;
    }
    if(ui->le_data->text() == ""){
        QMessageBox::warning(this, "Aviso", "Preencha o Campo Data.");
        return;
    }
    if(ui->te_description->toPlainText().isEmpty()){
        QMessageBox::warning(this, "Aviso", "Preencha o Campo Descrição.");
        return;
    }

    QString description = ui->te_description->toPlainText();
    QString date = ui->le_data->text();
    QString amount = ui->le_valor->text();

    if (ui->rb_receita->isChecked()){
        int category_id = db_takeIdCategory();
        QSqlQuery query;
        QString sql = "INSERT INTO incomes ( description, amount, category_id, date ) VALUES ( '"+ description +"', '"+ amount +"', '"+ QString::number(category_id) +"', '"+ date +"')";
        query.prepare(sql);

        if(query.exec()){
            qDebug() << "Dados Inseridos com Sucesso!";
            close();
        }else{
            qDebug() << "Falha ao Inserir Dados";
            qDebug() << sql;
            qDebug() << query.lastError().text();
        }



    }else if (ui->rb_despesa->isChecked()){
        int category_id = db_takeIdCategory();
        QSqlQuery query;
        QString sql = "INSERT INTO expenses ( description, amount, category_id, date ) VALUES ( '"+ description +"', '"+ amount +"', '"+ QString::number(category_id) +"', '"+ date +"')";
        query.prepare(sql);

        if(query.exec()){
            qDebug() << "Dados Inseridos com Sucesso!";
            close();
        }else{
            qDebug() << "Falha ao Inserir Dados";
            qDebug() << sql;
            qDebug() << query.lastError().text();
        }

    }else{
        QString notSelect_rb;
        notSelect_rb = "Escolha entre Receita ou Despesa.";
        QMessageBox::critical(this, "Falha", notSelect_rb);
    }
}

