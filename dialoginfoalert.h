#ifndef DIALOGINFOALERT_H
#define DIALOGINFOALERT_H

#include <QDialog>

namespace Ui {
class DialogInfoAlert;
}

class DialogInfoAlert : public QDialog
{
    Q_OBJECT

public:
    explicit DialogInfoAlert(QWidget *parent = nullptr);
    ~DialogInfoAlert();

    virtual void init(QString titolo,QString messaggio, QString image);

private:
    Ui::DialogInfoAlert *ui;
};

#endif // DIALOGINFOALERT_H
