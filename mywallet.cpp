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
        QFile::copy("/database/myWalletdb.db", user);//gravamos mas precisamos dar algumas permissoes para gravar a frente
        QFile::setPermissions(user, QFile::WriteOwner | QFile::ReadOwner);
        qDebug() << "O arquivo Inicial foi Copiado e as permissões de escrita foram definidas.";//dessa forma nosso bd esta presente no arquivo executavel também, e so vai copiar na 1ª vez
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
    QStringList infoList;
    infoList << "Receita: R$ 1000 \n" << "Despesa: R$ 500";

    QStringListModel *model = new QStringListModel(infoList);

    // Configure o modelo de dados para o QListView existente
    ui->listView->setModel(model);
}

