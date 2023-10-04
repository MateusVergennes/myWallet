#include "planejamentos.h"
#include "ui_planejamentos.h"

Planejamentos::Planejamentos(QWidget *parent) :QDialog(parent), ui(new Ui::Planejamentos) {
    ui->setupUi(this);

    comboBoxControl();
}

void Planejamentos::comboBoxControl(){
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
    ui->cb_CatExists->addItems(categoryName);
}

Planejamentos::~Planejamentos(){
    delete ui;
}


void Planejamentos::on_pb_addCat_clicked(){
    if(ui->le_newCat->text() == ""){
        QMessageBox::warning(this, "Aviso", "Preencha o Campo de Categoria Nova a ser Criada.");
        return;
    }

    QString categorie;

    categorie = ui->le_newCat->text();

    QSqlQuery query;
    QString sql = "INSERT INTO categories ( name ) VALUES ( '" + categorie + "')";
    query.prepare(sql);

    if(query.exec()){
        qDebug() << "Dados Inseridos com Sucesso!";
        close();
    }else{
        qDebug() << "Falha ao Inserir Dados";
        qDebug() << sql;
        qDebug() << query.lastError().text();
    }
}




void Planejamentos::on_cb_CatExists_currentTextChanged(const QString &arg1){
    ui->le_nameCategory->setText(arg1);
}


void Planejamentos::on_pb_deleteCat_clicked(){
    QString nameCategorie = ui->cb_CatExists->currentText();

    QSqlQuery query;
    QString sql = "DELETE FROM categories WHERE name = '" + nameCategorie + "'";
    qDebug() << sql;
    query.prepare(sql);

    if(query.exec()){
        close();
    }else{
        qDebug() << "Falha ao Deletar a Tarefa.";
    }
}


void Planejamentos::on_pb_editCat_clicked(){
    if(ui->le_nameCategory->text() == ""){
        QMessageBox::warning(this, "Aviso", "Campo não pode ficar Vazio");
            return;
    }

    QString newNameCategorie = ui->le_nameCategory->text();

    QSqlQuery query;
    QString sql = "UPDATE categories SET name = '" + newNameCategorie + "' WHERE name = '" + ui->cb_CatExists->currentText() + "'";
    query.prepare(sql);

    if(query.exec()){
            close();
    }else{
            qDebug() << "Falha ao Atualizar os Dados.";
    }
}

