#ifndef PLANEJAMENTOS_H
#define PLANEJAMENTOS_H

#include <QDialog>

namespace Ui {
class Planejamentos;
}

class Planejamentos : public QDialog
{
    Q_OBJECT

public:
    explicit Planejamentos(QWidget *parent = nullptr);
    ~Planejamentos();

private slots:
    void on_le_newCat_selectionChanged();

private:
    Ui::Planejamentos *ui;
};

#endif // PLANEJAMENTOS_H
