#ifndef CONSOLESALDO_H
#define CONSOLESALDO_H

#include <QDialog>
#include <QDebug>
#include <QString>

namespace Ui {
class consoleSaldo;
}

class consoleSaldo : public QDialog
{
    Q_OBJECT

public:
    explicit consoleSaldo(QWidget *parent = nullptr);
    ~consoleSaldo();


private slots:
    void getSaldo(const QString &);
    void on_btnSulje_clicked();
    void timerSlot();


signals:
    void closeWindow();

private:
    Ui::consoleSaldo *ui;
    int counter;
    QByteArray response_data;
    QString asiakkaanSaldo;
};

#endif // CONSOLESALDO_H
