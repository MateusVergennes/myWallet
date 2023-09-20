#ifndef MYWALLET_H
#define MYWALLET_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class myWallet; }
QT_END_NAMESPACE

class myWallet : public QMainWindow
{
    Q_OBJECT

public:
    myWallet(QWidget *parent = nullptr);
    ~myWallet();

private:
    Ui::myWallet *ui;
};
#endif // MYWALLET_H
