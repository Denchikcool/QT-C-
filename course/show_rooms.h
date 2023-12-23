#ifndef SHOW_ROOMS_H
#define SHOW_ROOMS_H

#include <QWidget>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

namespace Ui {
class show_rooms;
}

class show_rooms : public QWidget
{
    Q_OBJECT

public:
    explicit show_rooms(QWidget *parent = 0);
    ~show_rooms();

private slots:
    void on_next_page1_clicked();

    void on_next_page2_clicked();

    void on_next_page3_clicked();

    void on_next_page4_clicked();

    void on_previos_page4_clicked();

    void on_previos_page1_clicked();

    void on_previos_page2_clicked();

    void on_previos_page3_clicked();

    void on_stop_showing_clicked();

private:
    Ui::show_rooms *ui;
    QSqlDatabase db_rooms;
};

#endif // SHOW_ROOMS_H
