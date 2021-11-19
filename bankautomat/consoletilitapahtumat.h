#ifndef CONSOLETILITAPAHTUMAT_H
#define CONSOLETILITAPAHTUMAT_H

#include <QDialog>

namespace Ui {
class consoleTilitapahtumat;
}

class consoleTilitapahtumat : public QDialog
{
    Q_OBJECT

public:
    explicit consoleTilitapahtumat(QWidget *parent = nullptr);
    ~consoleTilitapahtumat();

private:
    Ui::consoleTilitapahtumat *ui;
};

#endif // CONSOLETILITAPAHTUMAT_H
