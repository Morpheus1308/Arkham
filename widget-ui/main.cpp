#include <Model.h>
#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    Model model;
    model.setFileName("/home/morten/ordbogen.aa");
    model.loadFromFileOrCreate();
    //model.loadFromFile();

    MainWindow window;
    window.show();
    window.setModel(&model);

    return app.exec();
}
