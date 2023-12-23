#ifndef SHOW_INFORMATION_CLIENTS_H
#define SHOW_INFORMATION_CLIENTS_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QIntValidator>
#include "add_client.h"


namespace Ui {
class show_information_clients;
}

class show_information_clients : public QWidget
{
    Q_OBJECT

public:
    explicit show_information_clients(QWidget *parent = 0);
    ~show_information_clients();

private slots:
    void on_exit_from_db_clicked();

    void on_remove_client_clicked();

    void on_clients_table_clicked(const QModelIndex &index);

    void on_refresh_data_clicked();

    //void on_clients_table_doubleClicked(const QModelIndex &index);

    //void on_find_button_clicked();

    void on_edit_data_clicked();

signals:
    void signal(QString, QString, QDateTime, QDateTime, QString, int, int, QPixmap);


private:
    Ui::show_information_clients *ui;
    QSqlDatabase db_information;
    QSqlTableModel *model;
    QSqlQueryModel *model_search;
    int currentRow;
    int idColumn;
    add_client *button_add_client;
    QIntValidator* intValidator;
};

#endif // SHOW_INFORMATION_CLIENTS_H
