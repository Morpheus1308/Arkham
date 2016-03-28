#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <Model.h>

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(Model &model, QWidget *parent = 0);
    ~LoginDialog();

signals:
    void loginCancelled();
    void loginSuccessFull(Resident *r);
private:
    class LoginDialogPrivate *d;
};

#endif // LOGINDIALOG_H
