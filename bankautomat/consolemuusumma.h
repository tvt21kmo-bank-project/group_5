#ifndef CONSOLEMUUSUMMA_H
#define CONSOLEMUUSUMMA_H

#include <QDialog>
#include <QDebug>
#include <QTimer>

namespace Ui {
class consoleMuuSumma;
}

class consoleMuuSumma : public QDialog
{
    Q_OBJECT

public:
    explicit consoleMuuSumma(QWidget *parent = nullptr);
    ~consoleMuuSumma();

private slots:
    void on_btnZero_clicked();
    void on_btnOne_clicked();
    void on_btnTwo_clicked();
    void on_btnThree_clicked();
    void on_btnFour_clicked();
    void on_btnFive_clicked();
    void on_btnSix_clicked();
    void on_btnSeven_clicked();
    void on_btnEight_clicked();
    void on_btnNine_clicked();
    void on_btnReset_clicked();
    void on_btnOK_clicked();
    void on_btnSulje_clicked();
    void clearText();

signals:
    void signalReset(int);
    void signalSumma(double);
private:
    Ui::consoleMuuSumma *ui;
    QString strluku;
    QTimer *objTimer;
    int counter, konsoliLuku, testi10;
    double maara;
};

#endif // CONSOLEMUUSUMMA_H
