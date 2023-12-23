#ifndef ADD_CLIENT_H
#define ADD_CLIENT_H

#include <QWidget>
#include <QLineEdit>
#include <QRegExp>
#include <QRegExpValidator>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QListView>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <show_rooms.h>
#include <QBuffer>
#include "calculator.h"

namespace Ui {
class add_client;
}

class add_client : public QWidget
{
    Q_OBJECT

public:
    explicit add_client(QWidget *parent = 0);
    ~add_client();

private slots:
    void on_button_load_clicked();

    void on_button_exit_sec_clicked();

    void on_check_FIO_clicked();

    void on_button_reset_clicked();

    void on_check_add_clicked();

    void on_button_save_clicked();

    void on_edit_clicked();

public slots:
    void slot(QString name, QString client_status, QDateTime date_start, QDateTime date_end, QString price_for_hour, int total_price, int number_room, QPixmap image_client);

private:
    Ui::add_client *ui;
    calculator *button_cal;
    QRegExpValidator *validator;
    QDateTime *ds;
    QDateTime *de;
    QSqlDatabase db_rooms_price;
    QSqlDatabase db_add_client;
    QCloseEvent *event;
};

#endif // ADD_CLIENT_H
