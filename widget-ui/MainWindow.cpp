#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QSortFilterProxyModel>
#include <Resident.h>
#include <QDebug>
#include <QItemSelectionModel>

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
    Resident* selected_resident;
    MainWindowPrivate(MainWindow*owner)
        : owner(owner),
          model(0),
          proxymodel(0),
          selected_resident(0)
    {
    }

    Resident *viewingResident()
    {
        if( ! model)
        {
            return 0;
        }
        Resident *r = model->viewingResident();
        if( ! r )
        {
            return 0;
        }
    }
    void applyPrivileges()
    {
        Resident *viewer = this->viewingResident();
        if( ! viewer ) return;
        bool may_create_resident =
                (viewer ->privileges() &
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
    connect(d->ui.action_Delete_selected, &QAction::triggered, [=](){
        if( ! d->selected_resident )
        {
            return;
        }
        qDebug() << "Deletes resident" << d->selected_resident->name();
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


    //When selection is changed, update actions accordingly
    connect(d->ui.residentsView->selectionModel(), &QItemSelectionModel::selectionChanged, [=](const QItemSelection & selected, const QItemSelection & deselected)
    {

        if( selected.indexes().size() == 0 )
        {
            return;
        }
        const QModelIndex &privilege_index = d->proxymodel->mapToSource(selected.indexes().first());
        const QModelIndex &model_index = d->model->mapToSource(privilege_index);

        d->selected_resident = static_cast<Resident*>(model_index.internalPointer());
        Resident *viewer = d->viewingResident();
        if( ! viewer )
        {
            return;
        }

        d->ui.action_Delete_selected->setEnabled( d->selected_resident->mayBeWrittenBy(viewer) );

    });

}

void MainWindow::showEvent(QShowEvent *event)
{
    if(d->model)
    {
        d->applyPrivileges();
    }

}
