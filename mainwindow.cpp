#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QList>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->init();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::init()
{
    ui->tb_view->setIcon(QIcon(":/monitor.png"));
    ui->b_controlla->setIcon(QIcon(":/arrow.png"));
    m_viewPrinc=new viewLista(this);
    m_viewPrinc->init();
    ui->l_layoutMain->addWidget(m_viewPrinc);
    m_viewCompare=new viewLista(this);
    m_viewCompare->init();
    ui->l_layoutMain->addWidget(m_viewCompare);
    m_viewRis=new viewRisultati(this);
    m_viewRis->init();
    ui->l_layoutRis->addWidget(m_viewRis);
    m_viewRis->setVisible(false);

    connect(ui->b_controlla, &QToolButton::clicked, this, [=]()
    {
        calcolaDifferenze();
    });

    connect(ui->tb_view, &QToolButton::clicked, this, [=]()
    {
        if(statoVisualizza==0)
        {
            m_viewPrinc->setVisible(false);
            m_viewCompare->setVisible(false);
            statoVisualizza=1;
        }
        else
        {
            m_viewPrinc->setVisible(true);
            m_viewCompare->setVisible(true);
            statoVisualizza=0;
        }
    });
}

void MainWindow::calcolaDifferenze()
{
    QMap<QString,QStringList> * m_mappaPrinc;
    QList<QStringList> * listaCompare;
    m_viewPrinc->popolaMappa();
    m_viewCompare->popolaListaCompare();
    m_mappaPrinc=m_viewPrinc->mappaPrinc();
    listaCompare=m_viewCompare->getListaCompare();
    if(!listaCompare) return;
    if(!m_mappaPrinc) return;
    QList<QStringList>::iterator it = listaCompare->begin();
    m_viewRis->createModello();
    for(;it!=listaCompare->end();++it)
    {
        QString keyCompare=(*it)[0];
        QString noKeyCompare=(*it)[1];
        if((*m_mappaPrinc).contains(keyCompare))
        {
            /*se contenuto controllo quanti valori ha la mappa*/
            int valMappa=0;
            valMappa=(*m_mappaPrinc)[keyCompare].count();
            if(valMappa==1)
            {
                /*controllo se valore è uguale*/
                if((*m_mappaPrinc)[keyCompare][0]==noKeyCompare)
                {
                    qDebug() << (*m_mappaPrinc)[keyCompare][0] << noKeyCompare;
                }
                else
                {
                    QStringList li=QStringList() << keyCompare << noKeyCompare <<"non corrisponde"<< (*m_mappaPrinc)[keyCompare][0];
                    m_viewRis->popolaModello(li,QColor("yellow"));
                }
            }
            else
            {
                QStringList li= QStringList() << keyCompare << noKeyCompare <<"Trovato più valori";
                for(int z=0; z<valMappa; z++)
                {
                    li.push_back((*m_mappaPrinc)[keyCompare][z]);
                }
                m_viewRis->popolaModello(li,QColor(209, 253, 255));
            }
        }
        else
        {
            QStringList li=QStringList() << keyCompare << noKeyCompare <<"non trovato";
            m_viewRis->popolaModello(li,QColor("red"));
        }
    }
    m_viewRis->setVisible(true);
}


