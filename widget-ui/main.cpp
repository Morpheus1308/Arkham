#include <Model.h>
#include <QApplication>

#include "MainWindow.h"
#include "LoginDialog.h"
#include <QDebug>
#include <Patient.h>
#include <Guard.h>

int main(int argc, char *argv[])
{
    RegisterResidentClass(Patient);
    RegisterResidentClass(Guard);

    QApplication app(argc, argv);
    Model model;
    model.setFileName("/home/morten/ordbogen.aa");
    model.makeTableModel();
    model.loadFromFileOrCreate();

    MainWindow window;
    window.setModel(&model);

    LoginDialog logindialog(model);
    logindialog.show();
    QObject::connect(&logindialog, SIGNAL(loginCancelled()), &app, SLOT(quit()));
    QObject::connect(&logindialog, &LoginDialog::loginSuccessFull, [&](Resident *r)
    {
        window.showMaximized();
        logindialog.hide();
    });

    return app.exec();
}
