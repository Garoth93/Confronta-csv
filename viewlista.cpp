#include "viewlista.h"
#include "ui_viewlista.h"
#include <QIcon>

viewLista::viewLista(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::viewLista)
{
    ui->setupUi(this);
}

viewLista::~viewLista()
{
    delete ui;
}

void viewLista::init(QString formatoSeparatore)
{
    m_modelPrincipale=nullptr;
    m_mappaPrinc=nullptr;
    listaCompare=nullptr;
    ui->b_addPrinc->setIcon(QIcon(":/entrata.png"));

    connect(ui->b_addPrinc, &QToolButton::clicked, this, [=]()
    {
        takeFile();
        if(pathFile=="")
            return;
        popolaModello();
        popolaMappa();
    });
}

void viewLista::popolaModello()
{
    QFile file(pathFile);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
        return;
    }

    QStringList rigaTotale;
    QStringList rigaInterna;
    QList<QStringList> listaRigheInterne;
    QString data;

    data=file.readAll();
    rigaTotale = data.split("\n");
    file.close();
    for (int x = 0; x < rigaTotale.size(); x++)
    {
        rigaInterna = rigaTotale.at(x).split(formatoSeparatore);
        listaRigheInterne.push_back(rigaInterna);
    }

    /*se esite un model lo elimino*/
    if(m_modelPrincipale) m_modelPrincipale->deleteLater();

    /*creo model nuovo*/
    m_modelPrincipale = new QStandardItemModel();

    QStringList ll;
    ll.insert(0,QString("GID"));
    ll.insert(1,QString("Area infratel"));

    /*setto intestazione colonne*/
    m_modelPrincipale->setHorizontalHeaderLabels(ll);

    /*setto model alla tableview*/
    ui->tv_princ->setModel(m_modelPrincipale);

    QList<QStringList>::iterator it=listaRigheInterne.begin();
    for(;it!=listaRigheInterne.end();++it)
    {
        QList<QStandardItem *>lItms;
        for(int x=0;x<(it)->size();x++)
        {
            lItms.insert(x,new QStandardItem((QString((*it)[x])).trimmed()));
        }
        m_modelPrincipale->appendRow(lItms);
    }
    ui->tv_princ->resizeColumnsToContents();
}

void viewLista::takeFile()
{
    QFileDialog * dialogTake;
    dialogTake=new QFileDialog();
    dialogTake->exec();
    QStringList nomeFIle;
    nomeFIle = dialogTake->selectedFiles();
    delete dialogTake;
    if(nomeFIle.count()!=0)
        pathFile=nomeFIle[0];
    else
        pathFile="";
}

bool viewLista::popolaMappa()
{
    if(!m_modelPrincipale) return false;
    if(m_mappaPrinc) delete m_mappaPrinc;
    m_mappaPrinc=new QMap<QString,QStringList>;
    int righeModelo=0;
    righeModelo=m_modelPrincipale->rowCount();
    for(int x=0;x<righeModelo;++x)
    {
        QString keyValue;
        QString noKeyValue;
        keyValue= m_modelPrincipale->index(x,0).data().toString();
        noKeyValue=  m_modelPrincipale->index(x,1).data().toString();
        (*m_mappaPrinc)[keyValue].push_back(noKeyValue);
    }
    return true;
}

bool viewLista::popolaListaCompare()
{
    if(!m_modelPrincipale) return false;
    if(listaCompare) delete listaCompare;
    listaCompare=new QList<QStringList>;
    int righeModelo=0;
    righeModelo=m_modelPrincipale->rowCount();
    for(int x=0;x<righeModelo;++x)
    {
        QString keyValue;
        QString noKeyValue;
        keyValue= m_modelPrincipale->index(x,0).data().toString();
        noKeyValue=  m_modelPrincipale->index(x,1).data().toString();
        listaCompare->push_back(QStringList() << keyValue << noKeyValue);
    }
    return true;
}

QMap<QString, QStringList> *viewLista::mappaPrinc() const
{
    return m_mappaPrinc;
}

QList<QStringList> *viewLista::getListaCompare() const
{
    return listaCompare;
}

QString viewLista::getFormatoSeparatore() const
{
    return formatoSeparatore;
}

void viewLista::setFormatoSeparatore(const QString &value)
{
    formatoSeparatore = value;
}

