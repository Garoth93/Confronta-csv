#ifndef DIALOGSEPARATORE_H
#define DIALOGSEPARATORE_H

#include <QDialog>

namespace Ui {
class DialogSeparatore;
}

class DialogSeparatore : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSeparatore(QWidget *parent = nullptr);
    ~DialogSeparatore();
    virtual void init(QString * separatore);

private:
    Ui::DialogSeparatore *ui;
};

#endif // DIALOGSEPARATORE_H
