#include <Model.h>
#include <QApplication>

#include "MainWindow.h"
#include "LoginDialog.h"
#include <QDebug>
#include <Patient.h>
#include <Guard.h>
#include <Alchemist.h>
#include <MedicalStaff.h>
#include <QDir>

#include <PrivilegeFilterProxyModel.h>


int main(int argc, char *argv[])
{
    RegisterResidentClass(Patient);
    RegisterResidentClass(Guard);
    RegisterResidentClass(MedicalStaff);
    RegisterResidentClass(Alchemist);

    QApplication app(argc, argv);
    Model model;
    model.setFileName(QDir::homePath()+"/arkham.arf");
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

    QObject::connect(&window, &MainWindow::logOut, [&]()
    {
       proxy.setViewingResident(0);
       proxy.invalidate();
       window.hide();
       logindialog.clearCredentials();
       logindialog.show();
    });

    return app.exec();
}
