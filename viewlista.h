#ifndef VIEWLISTA_H
#define VIEWLISTA_H

#include <QWidget>
#include <QStandardItemModel>
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QList>
#include <QMap>

namespace Ui {
class viewLista;
}

class viewLista : public QWidget
{
    Q_OBJECT

public:
    explicit viewLista(QWidget *parent = nullptr);
    ~viewLista();

    /** init*/
    virtual void init(QString formatoSeparatore);

    /** popola view con modello*/
    virtual void popolaModello();

    /** prendi path del file*/
    virtual void takeFile();

    /** riempio la mappa con oggetti da controllare*/
    virtual bool popolaMappa();

    virtual bool popolaListaCompare();

    QMap<QString, QStringList> *mappaPrinc() const;

    QList<QStringList> *getListaCompare() const;

    QString getFormatoSeparatore() const;
    void setFormatoSeparatore(const QString &value);

private:
    Ui::viewLista *ui;
    QStandardItemModel * m_modelPrincipale;
    QString pathFile="";
    QMap<QString,QStringList> * m_mappaPrinc;
    QList<QStringList> * listaCompare;
    QString formatoSeparatore=";";
};

#endif // VIEWLISTA_H
