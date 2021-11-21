#ifndef CONSOLETILITAPAHTUMAT_H
#define CONSOLETILITAPAHTUMAT_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class consoleTilitapahtumat;
}

class consoleTilitapahtumat : public QDialog
{
    Q_OBJECT

public:
    explicit consoleTilitapahtumat(QWidget *parent = nullptr);
    ~consoleTilitapahtumat();

private slots:
    void on_btnSulje_clicked();
    void timerSlot();

signals:
    void closeWindow();

private:
    Ui::consoleTilitapahtumat *ui;
    int counter;
};

#endif // CONSOLETILITAPAHTUMAT_H
