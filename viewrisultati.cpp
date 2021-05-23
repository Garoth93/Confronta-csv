#include "viewrisultati.h"
#include "ui_viewrisultati.h"
#include <dialoginfoalert.h>

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
    ui->b_salva->setIcon(QIcon(":/save.png"));
    ui->tb_reset->setIcon(QIcon(":/reset.png"));
    ui->cb_nonCorr->setChecked(true);
    ui->cb_multiValue->setChecked(true);
    ui->cb_nonTrovato->setChecked(true);

    connect(ui->b_salva, &QToolButton::clicked, this, [=]()
    {
        takeFile();
        if(pathFile!="")
            salvaDati();
    });
    connect(ui->tb_reset, &QToolButton::clicked, this, [=]()
    {
        resetFiltri();
        filtra();
    });
    connect(ui->cb_nonCorr, &QCheckBox::clicked, this, [=]()
    {
        filtra();
    });
    connect(ui->cb_multiValue, &QCheckBox::clicked, this, [=]()
    {
        filtra();
    });
    connect(ui->cb_nonTrovato, &QCheckBox::clicked, this, [=]()
    {
        filtra();
    });
}

void viewRisultati::createModello()
{
    /*se esite un model lo elimino*/
    if(m_modelPrincipale) m_modelPrincipale->deleteLater();

    /*creo model nuovo*/
    m_modelPrincipale = new QStandardItemModel();

    QStringList ll= QStringList() << "GID" << "Errore" << "Richiesta originale" << "As-built ";

    /*setto intestazione colonne*/
    m_modelPrincipale->setHorizontalHeaderLabels(ll);

    /*setto model alla tableview*/
    ui->tv_princ->setModel(m_modelPrincipale);
}

void viewRisultati::popolaModello(QStringList lista, QColor col, int tipoErr)
{
    QList<QStandardItem *>lItms;
    for(int xx=0; xx<lista.count();xx++)
    {
        lItms.insert(xx,new QStandardItem(QString(lista.value(xx))));
        lItms[xx]->setBackground(col);
    }
    lItms[1]->setData(tipoErr,Qt::UserRole+1);
    m_modelPrincipale->appendRow(lItms);
    ui->tv_princ->resizeColumnsToContents();
}

void viewRisultati::takeFile()
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

void viewRisultati::salvaDati()
{
    QFile file(QString("%1.csv").arg(pathFile));
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << file.errorString();
        return;
    }
    QTextStream stream(&file);
    if(!m_modelPrincipale) return;
    int righeModelo=0;
    righeModelo=m_modelPrincipale->rowCount();
    int colRiga=0;
    colRiga=m_modelPrincipale->columnCount();
    stream << "GID;" << "Errore;" << "Richiesta originale;" << "As-built " << "\n";
    for(int x=0;x<righeModelo;++x)
    {
        for(int y=0; y<colRiga; ++y)
        {
            QString val=m_modelPrincipale->index(x,y).data().toString();
            if(y<(colRiga-1))
                stream << QString("%1;").arg(val);
            else
                stream << val << "\n";
        }
    }
    file.close();
    DialogInfoAlert * dialog;
    dialog=new DialogInfoAlert(this);
    dialog->init("OK","Salvataggio riuscito","Beagle_Stupendo.png");
    dialog->exec();
}

void viewRisultati::filtra()
{
    if(!m_modelPrincipale) return;
    int righeModelo=0;
    righeModelo=m_modelPrincipale->rowCount();
    qDebug() << righeModelo;
    for(int x=0;x<righeModelo;++x)
    {
        int val=m_modelPrincipale->index(x,1).data(Qt::UserRole+1).toInt();
        qDebug() << val;
        if(val==1)
        {
            if(ui->cb_nonCorr->isChecked())
                ui->tv_princ->showRow(x);
            else
                ui->tv_princ->hideRow(x);
        }else if(val==2)
        {
            if(ui->cb_multiValue->isChecked())
                ui->tv_princ->showRow(x);
            else
                ui->tv_princ->hideRow(x);
        }
        else if(val==3)
        {
            if(ui->cb_nonTrovato->isChecked())
                ui->tv_princ->showRow(x);
            else
                ui->tv_princ->hideRow(x);
        }
    }
}

void viewRisultati::resetFiltri()
{
    ui->cb_nonCorr->setChecked(false);
    ui->cb_multiValue->setChecked(false);
    ui->cb_nonTrovato->setChecked(false);
}
