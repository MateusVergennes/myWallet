#include "mywallet.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myWallet w;
    w.show();
    return a.exec();
}
