#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include <QDebug>
#include <Model.h>
#include <QMessageBox>
#include <QInputDialog>
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


    //Perform login
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


    //When the user has forgot his password.
    connect(d->ui.forgotpassword, &QLabel::linkActivated, [&](){
        QString email = QInputDialog::getText(this, tr("Send New Password"), tr("Enter your e-mail, and we will send you a new password."));
        if(email.trimmed() != "")
        {
            model.createNewPasswordFor(email);
            QMessageBox::information(this, tr("New Password Sent"), tr("A new password has been created and sent to %1").arg(email));
        }
    });


    //When the user requests a new account.
    connect(d->ui.createaccount, &QLabel::linkActivated, [&](){
        QString email = QInputDialog::getText(this, tr("Create Account"), tr("Enter your e-mail, and we will create a new account and send you a password.\nYou will be granted guard privileges!"));
        if(email.trimmed() != "")
        {

            model.createNewGuard(email);
            QMessageBox::information(this, tr("Account created"), tr("A new password has been created and a password sent to %1").arg(email));
        }

    });

}

LoginDialog::~LoginDialog()
{
    delete d;
}

void LoginDialog::clearCredentials()
{
    d->ui.email->setText("");
    d->ui.email->setFocus();
    d->ui.password->setText("");
}
