#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractItemModel>
#include <PrivilegeFilterProxyModel.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setModel(PrivilegeFilterProxyModel *model);

protected:
    void showEvent(QShowEvent * event);

signals:
    void logOut();

private:
    class MainWindowPrivate *d;
};

#endif // MAINWINDOW_H
