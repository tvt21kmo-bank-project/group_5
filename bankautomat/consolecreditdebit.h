#ifndef CONSOLECREDITDEBIT_H
#define CONSOLECREDITDEBIT_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class consoleCreditDebit;
}

class consoleCreditDebit : public QDialog
{
    Q_OBJECT

public:
    explicit consoleCreditDebit(QWidget *parent = nullptr);
    ~consoleCreditDebit();

private slots:
    void on_btnDebit_clicked();
    void on_btnCredit_clicked();
    void slotCardID(const QString &);

private:
    Ui::consoleCreditDebit *ui;
    QString korttiID;
};

#endif // CONSOLECREDITDEBIT_H
