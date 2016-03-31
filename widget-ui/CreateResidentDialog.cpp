#include "CreateResidentDialog.h"
#include "ui_CreateResidentDialog.h"

#include <Model.h>
#include <functional>
#include <QDebug>
#include <Guard.h>

#include <QMessageBox>

class CreateResidentDialogPrivate
{

public:
    Ui::CreateResidentDialog ui;
    Model *model;

    void clearForm()
    {
        ui.type_selector->setCurrentIndex(0);
        ui.gender_select->setCurrentIndex(0);
        ui.name_edit->setText("");
        ui.email_edit->setText("");
        ui.title_edit->setText("");
        ui.sanity_edit->setValue(0);
        ui.birthdate_edit->setDate(QDate::currentDate().addYears(-18));
        ui.type_selector->setFocus();
    }
};


CreateResidentDialog::CreateResidentDialog(Model *model, QWidget *parent) :
    QDialog(parent),
    d(new CreateResidentDialogPrivate())
{
    d->ui.setupUi(this);
    d->model = model;

    foreach(const QString class_name, Resident::registeredCreators().keys())
    {
        d->ui.type_selector->addItem(class_name, class_name);
    }

    d->ui.gender_select->addItem(tr("Male"), Resident::Male);
    d->ui.gender_select->addItem(tr("Female"), Resident::Female);
    d->ui.gender_select->addItem(tr("Hermaphrodite"), Resident::Hermaphrodite);
    d->ui.gender_select->addItem(tr("Not sure"), Resident::NotSure);

    this->setModal(false);

    connect(d->ui.create_button, &QPushButton::clicked, [=](){

        if(d->ui.email_edit->text() == "" )
        {
            QMessageBox::critical(this, tr("Can Not Create New Resident"), tr("You shall specify an email for the new resident."));
            return;
        }

        QString classname = d->ui.type_selector->currentData().toString();
        Resident *resident = Resident::registeredCreators()[classname]();
        resident->setTitle(d->ui.title_edit->text());
        resident->setName(d->ui.name_edit->text());
        resident->setSanity(d->ui.sanity_edit->value());
        resident->setBirthDate(d->ui.birthdate_edit->date());
        resident->setGender(Resident::Gender(d->ui.gender_select->currentData().toInt()));
        resident->setEmail(d->ui.email_edit->text());
        if( model->addResident(resident) )
        {
            d->clearForm();
        }
        else
        {
            QMessageBox::critical(this, tr("Can Not Create New Resident"), tr("The email address %1 is already in use. Specify a unique one.").arg(resident->email()));
            }
    });


    //When we are done, release allocated memory.
    connect(d->ui.cancel_button, &QPushButton::clicked, this, &QDialog::reject);
    connect(this, &QDialog::finished, this, [=](){
        this->deleteLater();
    });

}

CreateResidentDialog::~CreateResidentDialog()
{
    delete d;
}

void CreateResidentDialog::showEvent(QShowEvent *)
{
    d->clearForm();
}
