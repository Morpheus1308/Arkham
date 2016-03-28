#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include <QDebug>
#include <Model.h>
#include <QMessageBox>
#include <Resident.h>

class LoginDialogPrivate
{
public:

    LoginDialogPrivate(Model &model)
        : model(model)
    {
    }

    Ui::LoginDialog ui;
    Model &model;
};

LoginDialog::LoginDialog(Model &model, QWidget *parent) :
    QDialog(parent),
    d(new LoginDialogPrivate(model))
{
    d->ui.setupUi(this);
    connect(d->ui.cancel_button, SIGNAL(clicked(bool)), this, SIGNAL(loginCancelled()));

    connect(d->ui.login_button, &QPushButton::clicked, [=](){
        bool success = false;
        Resident *r = this->d->model.getResidentByEmail(d->ui.email->text());
        if(r)
        {
            success = r->matchesPassword(d->ui.password->text());
        }
        if (! success )
        {
            QMessageBox::critical(this, tr("Login Failed"), tr("Your provided password and email did not match. Try again."));
        }
        else
        {
            emit this->loginSuccessFull(r);
        }
    });
}

LoginDialog::~LoginDialog()
{
    delete d;
}
