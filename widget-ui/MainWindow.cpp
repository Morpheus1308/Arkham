#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QSortFilterProxyModel>
#include <Resident.h>
#include <QDebug>
#include <QLineEdit>
#include <QItemSelectionModel>
#include <Model.h>
#include "CreateResidentDialog.h"

class MyProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:

    MyProxy(Model *model)
    {
        this->model = model;
    }

    void setFilterText(const QString &phrase)
    {
        search_term = phrase.trimmed();
        this->invalidate();
    }

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &) const
    {
        if(search_term == "") return true;
        Resident *r = model->residents()[sourceRow];
        QString gender_string;
        switch(r->gender())
        {
        case Resident::Male: gender_string = "Male"; break;
        case Resident::Female: gender_string = "Female";break;
        case Resident::Hermaphrodite: gender_string = "Hermaphrodite";break;
        case Resident::NotSure: gender_string = "Not quite sure";break;
        default:
            break;
        }

        return
                r->title().contains(search_term, Qt::CaseInsensitive)
                | r->name().contains(search_term, Qt::CaseInsensitive)
                | r->email().contains(search_term, Qt::CaseInsensitive)
                | QString::number(r->sanity()).contains(search_term, Qt::CaseInsensitive)
                | r->formattedBirthDate().contains(search_term, Qt::CaseInsensitive)
                | gender_string.contains(search_term, Qt::CaseInsensitive)
                | r->className().contains(search_term, Qt::CaseInsensitive);


    }


private:
    Model *model;
    QString search_term;
};

#include "MainWindow.moc"

class MainWindowPrivate
{
private:
    MainWindow *owner;

public:
    Model *model;
    PrivilegeFilterProxyModel *privilege_proxied_model;
    MyProxy *filter_proxy_model;
    Resident* selected_resident;
    MainWindowPrivate(MainWindow*owner)
        : owner(owner),
          privilege_proxied_model(0),
          filter_proxy_model(0),
          selected_resident(0)
    {
    }

    Resident *viewingResident()
    {
        if( ! privilege_proxied_model)
        {
            return 0;
        }
        Resident *r = privilege_proxied_model->viewingResident();
        if( ! r )
        {
            return 0;
        }
        return 0;
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
    d->ui.toolBar->addAction(d->ui.action_Save);
    d->ui.toolBar->addAction(d->ui.action_Add_Resident);
    d->ui.toolBar->addAction(d->ui.action_Delete_selected);

    QLineEdit *search_edit = new QLineEdit();
    search_edit->setPlaceholderText(tr("Search in residents..."));
    d->ui.toolBar->addWidget(search_edit);
    connect(search_edit, &QLineEdit::textChanged, [=](const QString& search_phrase)
    {
        if ( ! d->filter_proxy_model )
        {
            return;
        }
        d->filter_proxy_model->setFilterText(search_phrase);
    });

    connect(d->ui.action_Quit, &QAction::triggered, qApp, &QCoreApplication::quit);
    connect(d->ui.action_Log_out, &QAction::triggered, this, &MainWindow::logOut);

    connect(d->ui.action_Delete_selected, &QAction::triggered, [=](){
        if( ! d->selected_resident )
        {
            return;
        }
        d->model->removeResident(d->selected_resident);
    });

    connect(d->ui.action_Add_Resident, &QAction::triggered, [=](){
        CreateResidentDialog *dialog = new CreateResidentDialog(d->model);
        dialog->show();
    });

}

MainWindow::~MainWindow()
{
    delete d;
}

void MainWindow::setModel(PrivilegeFilterProxyModel *model)
{

    d->model = dynamic_cast<Model*>(model->sourceModel());
    if( ! d->model )
    {
        return;
    }

    d->filter_proxy_model = new MyProxy(d->model);
    d->filter_proxy_model->setSourceModel(model);
    d->ui.residentsView->setModel(d->filter_proxy_model);
    d->privilege_proxied_model = model;


    connect(d->ui.action_Save, &QAction::triggered, d->model, &Model::saveToFile);

    //When selection is changed, update actions accordingly
    connect(d->ui.residentsView->selectionModel(), &QItemSelectionModel::selectionChanged, [=](const QItemSelection & selected, const QItemSelection & )
    {

        if( selected.indexes().size() == 0 )
        {
            return;
        }
        const QModelIndex &privilege_index = d->filter_proxy_model->mapToSource(selected.indexes().first());
        const QModelIndex &model_index = d->privilege_proxied_model->mapToSource(privilege_index);

        d->selected_resident = static_cast<Resident*>(model_index.internalPointer());
        Resident *viewer = d->viewingResident();
        if( ! viewer )
        {
            return;
        }

        d->ui.action_Delete_selected->setEnabled( d->selected_resident->mayBeWrittenBy(viewer) );

    });

    connect(d->model, &Model::hasUnsavedChangesChanged, d->ui.action_Save, &QAction::setEnabled);
    d->ui.action_Save->setEnabled(d->model->hasUnsavedChanges());
}

void MainWindow::showEvent(QShowEvent *)
{
    if(d->privilege_proxied_model)
    {
        d->applyPrivileges();
    }

}
