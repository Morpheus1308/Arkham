#include <Model.h>
#include <QApplication>

#include "MainWindow.h"
#include "LoginDialog.h"
#include <QDebug>
#include <Patient.h>
#include <Guard.h>
#include <PrivilegeFilterProxyModel.h>


int main(int argc, char *argv[])
{
    RegisterResidentClass(Patient);
    RegisterResidentClass(Guard);

    QApplication app(argc, argv);
    Model model;
    model.setFileName("/home/morten/ordbogen.aa");
    model.makeTableModel();
    model.loadFromFileOrCreate();
    PrivilegeFilterProxyModel proxy;
    proxy.setSourceModel(&model);

    MainWindow window;
    window.setModel(&proxy);

    LoginDialog logindialog(model);
    logindialog.show();
    QObject::connect(&logindialog, SIGNAL(loginCancelled()), &app, SLOT(quit()));
    QObject::connect(&logindialog, &LoginDialog::loginSuccessFull, [&](Resident *r)
    {
        proxy.setViewingResident(r);
        proxy.invalidate();
        window.showMaximized();
        logindialog.hide();
    });

    return app.exec();
}
