#include "dialoginfoalert.h"
#include "ui_dialoginfoalert.h"

DialogInfoAlert::DialogInfoAlert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogInfoAlert)
{
    ui->setupUi(this);
}

DialogInfoAlert::~DialogInfoAlert()
{
    delete ui;
}

void DialogInfoAlert::init(QString titolo, QString messaggio, QString image)
{
    this->setWindowTitle(titolo);
    ui->l_mainText->setText(messaggio);
    QString testoImage=QString(":/%1").arg(image);
    QPixmap immagine(testoImage);
    QLabel *imageLabel = new QLabel();
    imageLabel->setPixmap(immagine);
    ui->horizontalLayout_2->addWidget(imageLabel);

    connect(ui->b_button1, &QPushButton::clicked, this, [=]()
    {
        this->close();
    });
}
