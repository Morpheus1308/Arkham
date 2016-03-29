#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <Model.h>
#include <QDebug>
#include <Patient.h>
#include <Guard.h>


int main(int argc, char *argv[])
{

    RegisterResidentClass(Patient);
    RegisterResidentClass(Guard);

    QGuiApplication app(argc, argv);
    Model model;
    model.setFileName("/home/morten/ordbogen.aa");
    model.loadFromFileOrCreate();
    model.makeListModel();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("MyModel", &model);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}

