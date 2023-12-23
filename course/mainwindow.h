#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "add_client.h"
#include "show_rooms.h"
#include "show_information_clients.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_exit_clicked();
    void TimerSlot();

    void on_button_show_rooms_clicked();

    void on_show_database_clicked();

    void on_button_add_client_clicked();

private:
    Ui::MainWindow *ui;
    add_client *add_client_button;
    show_rooms *show_rooms_button;
    show_information_clients *show_database_button;


    QTimer *timer;
    int ms;
    int s;
    int m;
};

#endif // MAINWINDOW_H
