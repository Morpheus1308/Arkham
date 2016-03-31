#ifndef CREATERESIDENTDIALOG_H
#define CREATERESIDENTDIALOG_H

#include <QDialog>

class CreateResidentDialog : public QDialog
{
    Q_OBJECT

public:
    CreateResidentDialog(class Model *model, QWidget *parent = 0);
    ~CreateResidentDialog();

protected:
    void showEvent(QShowEvent * event);

private:
    class CreateResidentDialogPrivate *d;
};

#endif // CREATERESIDENTDIALOG_H
