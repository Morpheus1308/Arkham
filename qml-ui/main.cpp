#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <Model.h>
#include <QDebug>
#include <Patient.h>
#include <Guard.h>
#include <Alchemist.h>
#include <MedicalStaff.h>
#include <QtQml>
#include <PrivilegeFilterProxyModel.h>


int main(int argc, char *argv[])
{

    RegisterResidentClass(Patient);
    RegisterResidentClass(Guard);
    RegisterResidentClass(MedicalStaff);
    RegisterResidentClass(Alchemist);

    qmlRegisterType<Resident>("dk.winkler.morten.Arkham", 1, 0, "Resident");
    qmlRegisterType<Model>("dk.winkler.morten.Arkham", 1, 0, "Model");

    QGuiApplication app(argc, argv);
    Model model;
    model.setFileName("/home/morten/ordbogen.aa");
    model.loadFromFileOrCreate();
    model.makeListModel();

    PrivilegeFilterProxyModel proxy;
    proxy.setSourceModel(&model);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("MyModel", &proxy);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}

