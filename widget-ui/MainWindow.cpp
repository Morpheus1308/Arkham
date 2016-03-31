#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QSortFilterProxyModel>

class MyProxy : public QSortFilterProxyModel
{
    Q_OBJECT

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
    {
       return true;
    }
};

#include "MainWindow.moc"

class MainWindowPrivate
{
private:
    MainWindow *owner;

public:
    MainWindowPrivate(MainWindow*owner)
        : owner(owner)
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
    d->ui.toolBar->addAction(d->ui.action_Log_out);
    d->ui.toolBar->addAction(d->ui.action_Quit);
    d->ui.toolBar->addSeparator();
    d->ui.toolBar->addAction(d->ui.action_Add_Resident);
    d->ui.toolBar->addAction(d->ui.action_Delete_selected);


    connect(d->ui.action_Quit, &QAction::triggered, qApp, &QCoreApplication::quit);
    connect(d->ui.action_Log_out, &QAction::triggered, this, &MainWindow::logOut);

}

MainWindow::~MainWindow()
{
    delete d;
}

void MainWindow::setModel(QAbstractItemModel *model)
{
    QSortFilterProxyModel *proxymodel = new MyProxy();
    proxymodel->setSourceModel(model);
    d->ui.residentsView->setModel(proxymodel);
}
