#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "consolemain.h"
#include <QMainWindow>
#include <QKeyEvent>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void signalKirjaudu();

private slots:
    void on_btnKirjaudu_clicked();
    void loginSlot();

private:
    Ui::MainWindow *ui;
    consoleMain *objConMain = new consoleMain;

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

};
#endif // MAINWINDOW_H
