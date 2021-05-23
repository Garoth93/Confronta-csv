#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "viewlista.h"
#include <viewrisultati.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init();

public slots:

    void calcolaDifferenze();

private:
    Ui::MainWindow *ui;
    viewLista * m_viewPrinc;
    viewLista * m_viewCompare;
    viewRisultati * m_viewRis;
    int statoVisualizza=0;
    QString formatoSeparatore=";";

};
#endif // MAINWINDOW_H
