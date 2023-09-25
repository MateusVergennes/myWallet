#ifndef ADD_IORR_H
#define ADD_IORR_H

#include <QDialog>

namespace Ui {
class Add;
}

class Add : public QDialog
{
    Q_OBJECT

public:
    explicit Add(QWidget *parent = nullptr);
    ~Add();

private:
    Ui::Add *ui;
};

#endif // ADD_IORR_H
