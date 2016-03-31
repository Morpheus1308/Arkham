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

void MainWindow::setModel(QAbstractItemModel *model)
{
    QSortFilterProxyModel *proxymodel = new MyProxy();
    proxymodel->setSourceModel(model);
    d->ui.residentsView->setModel(proxymodel);
}
