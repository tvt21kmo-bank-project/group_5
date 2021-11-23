#ifndef CREDITDEBIT_H
#define CREDITDEBIT_H

#include <QDialog>

namespace Ui {
class creditDebit;
}

class creditDebit : public QDialog
{
    Q_OBJECT

public:
    explicit creditDebit(QWidget *parent = nullptr);
    ~creditDebit();

private slots:
    void on_btnCredit_clicked();

    void on_btnDebit_clicked();

private:
    Ui::creditDebit *ui;
};

#endif // CREDITDEBIT_H
