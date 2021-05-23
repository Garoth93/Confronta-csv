#include "viewrisultati.h"
#include "ui_viewrisultati.h"

viewRisultati::viewRisultati(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::viewRisultati)
{
    ui->setupUi(this);
}

viewRisultati::~viewRisultati()
{
    delete ui;
}

void viewRisultati::init()
{
    m_modelPrincipale=nullptr;

    connect(ui->b_salva, &QToolButton::clicked, this, [=]()
    {
    });
}

void viewRisultati::createModello()
{
    /*se esite un model lo elimino*/
    if(m_modelPrincipale) m_modelPrincipale->deleteLater();

    /*creo model nuovo*/
    m_modelPrincipale = new QStandardItemModel();

    QStringList ll= QStringList() << "key" << "val" << "err"
                                  << "proposto" << "proposto" << "proposto" << "proposto";

    /*setto intestazione colonne*/
    m_modelPrincipale->setHorizontalHeaderLabels(ll);

    /*setto model alla tableview*/
    ui->tv_princ->setModel(m_modelPrincipale);
}

void viewRisultati::popolaModello(QStringList lista, QColor col)
{
    QList<QStandardItem *>lItms;
    for(int xx=0; xx<lista.count();xx++)
    {
        lItms.insert(xx,new QStandardItem(QString(lista.value(xx))));
        lItms[xx]->setBackground(col);
    }
    m_modelPrincipale->appendRow(lItms);
    ui->tv_princ->resizeColumnsToContents();
}
