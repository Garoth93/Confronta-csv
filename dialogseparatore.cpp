#include "dialogseparatore.h"
#include "ui_dialogseparatore.h"

DialogSeparatore::DialogSeparatore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSeparatore)
{
    ui->setupUi(this);
}

DialogSeparatore::~DialogSeparatore()
{
    delete ui;
}

void DialogSeparatore::init(QString * separatore)
{
    this->setWindowTitle("Separatore");
    connect(ui->pushButton, &QPushButton::clicked, this, [=]()
    {
        (*separatore)=";";
        if(ui->r_virgola->isChecked())
            (*separatore)=",";
        else if(ui->r_puntoVirgola->isChecked())
            (*separatore)=";";
        this->close();
    });
}
