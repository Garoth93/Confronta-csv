#ifndef VIEWRISULTATI_H
#define VIEWRISULTATI_H

#include <QWidget>
#include <QStandardItemModel>
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QList>
#include <QMap>
#include <QColor>

namespace Ui {
class viewRisultati;
}

class viewRisultati : public QWidget
{
    Q_OBJECT

public:
    explicit viewRisultati(QWidget *parent = nullptr);
    ~viewRisultati();

    /** init*/
    virtual void init();

    /** popola view con modello*/
    virtual void createModello();

    virtual void popolaModello(QStringList lista, QColor col);

private:
    Ui::viewRisultati *ui;
    QStandardItemModel * m_modelPrincipale;
    QString pathFile="";
};

#endif // VIEWRISULTATI_H
