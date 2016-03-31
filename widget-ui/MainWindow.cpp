#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QSortFilterProxyModel>
#include <Resident.h>
#include <QDebug>

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
    PrivilegeFilterProxyModel *model;
    QSortFilterProxyModel *proxymodel;

    MainWindowPrivate(MainWindow*owner)
        : owner(owner),
          model(0),
          proxymodel(0)
    {
    }

    void applyPrivileges()
    {
        if( ! model)
        {
            return;
        }
        Resident *r = model->viewingResident();
        if( ! r )
        {
            return;
        }
        bool may_create_resident =
                (r->privileges() &
                (Resident::MayWriteAlchemist
                 | Resident::MayWriteGuards
                 | Resident::MayWritePatients
                 | Resident::MayWriteMedicalStaff
                )
                );
        ui.action_Add_Resident->setEnabled( may_create_resident );
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

    connect(d->ui.residentsView, &QAbstractItemView::clicked, [=](const QModelIndex &index)
    {
        qDebug() << "Resident clicked";
        const QModelIndex &privilege_index = d->proxymodel->mapToSource(index);
        const QModelIndex &model_index = d->model->mapToSource(privilege_index);


        Resident *resident = static_cast<Resident*>(model_index.internalPointer());
        qDebug() << resident->name();
    });

}

MainWindow::~MainWindow()
{
    delete d;
}

void MainWindow::setModel(PrivilegeFilterProxyModel *model)
{
    d->proxymodel = new MyProxy();
    d->proxymodel->setSourceModel(model);
    d->ui.residentsView->setModel(d->proxymodel);
    d->model = model;


}

void MainWindow::showEvent(QShowEvent *event)
{
    if(d->model)
    {
        d->applyPrivileges();
    }

}
