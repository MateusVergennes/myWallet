#include "mywallet.h"
#include "ui_mywallet.h"

myWallet::myWallet(QWidget *parent): QMainWindow(parent), ui(new Ui::myWallet){
    ui->setupUi(this);

    start();
    db.setDatabaseName(user);
    //se ele estiver aberto (arquivo encontrado), senao (falha)
    !db.open() ? qDebug() << "Falha ao Encontrar o Arquivo do Banco: " + user : qDebug() << "Arquivo do Banco Encontrado com Sucesso!";

    listViewDados();
}

void myWallet::start(){
    QFile quser(user);


    if(!quser.exists()){//se o arquivo ainda n existir, vai copiar o db para o user
        if (QFile::exists(":/database/myWallet.db")) {// Verifica se o arquivo de origem existe como um recurso incorporado
            QFile::copy(":/database/myWallet.db", user);//gravamos mas precisamos dar algumas permissoes para gravar a frente
            QFile::setPermissions(user, QFile::WriteOwner | QFile::ReadOwner);
            qDebug() << "O arquivo Inicial foi Copiado e as permissões de escrita foram definidas.";//dessa forma nosso bd esta presente no arquivo executavel também, e so vai copiar na 1ª vez
        }else{
            qDebug() << "Falha ao encontrar o arquivo para Copia.";
        }
    }
}

myWallet::~myWallet(){
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

void myWallet::listViewDados(){
    QSqlQuery query;
    QString sql = "SELECT * FROM expenses INNER JOIN categories ON expenses.category_id = categories.category_id UNION ALL "
                  "SELECT * FROM incomes INNER JOIN categories ON incomes.category_id = categories.category_id ORDER BY date DESC";
    query.prepare(sql);

    if(query.exec()){
        int i = 0;

        ui->tableWidget->setColumnCount(5);// colunas(id, description, value)
        while(query.next()){
            ui->tableWidget->insertRow(i);//para mostrar os dados da linha

            //tratamento para mostrar data ao usuario de maneira intuitiva
            QString inputString = query.value(4).toString();
            inputString.insert(2, '/').insert(5, '/').insert(10, ' ').insert(13, ':').insert(16, ':');

            //setando as colunas (aba mais de cima)
            ui->tableWidget->setItem(i, 0, new QTableWidgetItem(query.value(0).toString() ) );//Linha, coluna, valor como construtor //id // o new ja faz pegar o construtor
            ui->tableWidget->setItem(i, 1, new QTableWidgetItem(query.value(1).toString() ) );//descricao
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(query.value(2).toString() ) );//valor
            ui->tableWidget->setItem(i, 3, new QTableWidgetItem(inputString               ) );//data
            ui->tableWidget->setItem(i, 4, new QTableWidgetItem(query.value(7).toString() ) );//name category

            for (int j=0;j<5;j++){
                if (query.value(5) == "incomes"){//tipo de tabela se é de incomes(receita) ou expenses(Despesas)
                    QColor backgroundColor;
                    backgroundColor = QColor(0, 255, 0);//verde
                    ui->tableWidget->item(i, j)->setBackground(backgroundColor);
                }
                if (query.value(5) == "expenses"){
                    QColor backgroundColor;
                    backgroundColor = QColor(255, 0, 0);//vermelho
                    ui->tableWidget->item(i, j)->setBackground(backgroundColor);
                }
            }

            i++;


            //definindo cabecalho
            QStringList headers = {"ID", "Descrição", "Valor", "Data/Hora", "Categoria"};
                                                                             ui->tableWidget->setHorizontalHeaderLabels(headers);

            //para definir tamanho das Colunas:
            ui->tableWidget->setColumnWidth(0, 60);//coluna 1 com 60 de largura
            ui->tableWidget->setColumnWidth(1, 150);
            ui->tableWidget->setColumnWidth(2, 150);
            ui->tableWidget->setColumnWidth(3, 150);
            ui->tableWidget->setColumnWidth(4, 150);

            while(i <ui->tableWidget->rowCount()){
                ui->tableWidget->removeRow(i);//para excluir todos os itens quando forem removidos da tabela, sem deixar tracos (vai dar um clear na tabela mostrada)
            }

            ui->tableWidget->verticalHeader()->setVisible(false);//para nao ter a numeracao de linha ao lado
        }
    }else{
        qDebug() << "Falha ao Consultar os Dados no Banco de Dados";
    }

}


void myWallet::on_pushButton_clicked(){
    Add_data TelaAdd;

    if(!db.isOpen()){
        QMessageBox::warning(this, "Aviso", "Falha ao Conectar ao Banco de Dados");
        return;
    }

    TelaAdd.exec();
    listViewDados();
}


void myWallet::on_tableWidget_cellClicked(int row, int column){
    column = 0;
    int id = ui->tableWidget->item(row, column)->text().toInt();//pega o a linha que foi clicada, a coluna 0(que é a do id) e como id é int, converte ele
    QString description = ui->tableWidget->item(row, 1)->text();//para o conteudo da descricao
    QString valor = ui->tableWidget->item(row, 2)->text();
    QString categoria = ui->tableWidget->item(row, 4)->text();

    QTableWidgetItem *item = ui->tableWidget->item(row, column);
    QBrush backgroundBrush;
    QColor backgroundColor;
    QString typeTable;
    if (item) {
        backgroundBrush = item->background();
        backgroundColor = backgroundBrush.color();
    }
    if (backgroundColor.name() == "#ff0000"){//para saber de qual tabela pertence
        typeTable = "expenses";
    }else if(backgroundColor.name() == "#00ff00"){
        typeTable = "incomes";
    }else{
        return;
    }
    Editar e(this, id, description, typeTable, valor, categoria);
    e.exec();//para abrir a janela .ui
    listViewDados();
}

