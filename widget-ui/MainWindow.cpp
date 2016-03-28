#include "MainWindow.h"
#include "ui_MainWindow.h"

class MainWindowPrivate
{
private:
    MainWindow *owner;

public:
    MainWindowPrivate(MainWindow*owner)
        : owner(owner)
    {
    }

    MainWindowPrivate()
    {
    }

public:
    Ui::MainWindow ui;
};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    d(new MainWindowPrivate(this))
{
    d->ui.setupUi(this);
}

MainWindow::~MainWindow()
{
    delete d;
}

void MainWindow::setModel(Model *model)
{
    d->ui.residentsView->setModel(model);
}
