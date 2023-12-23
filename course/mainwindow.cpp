#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    add_client_button = new add_client();
    show_rooms_button = new show_rooms();
    show_database_button = new show_information_clients();
    connect(ui->button_exit, SIGNAL(clicked()), qApp, SLOT(closeAllWindows()));

    timer = new QTimer(this);
    ms = 0;
    s = 0;
    m = 0;
    connect(timer, SIGNAL(timeout()),this,SLOT(TimerSlot()));
    timer->start(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exit_clicked()
{
    //close();
}

void MainWindow::TimerSlot()
{
    ms++;
    if(ms>=1000){
        ms = 0;
        s++;
    }
    if(s>=60){
        s = 0;
        m++;
    }
    if (s >= 0 && s < 10) {
        ui->minuts->setText((m >= 0 && m < 10) ? "0" + QString::number(m) + " :" : QString::number(m) + " :");
        ui->seconds->setText("0" + QString::number(s));
    } else {
        ui->minuts->setText((m >= 0 && m < 10) ? "0" + QString::number(m) + " :" : QString::number(m) + " :");
        ui->seconds->setText(QString::number(s));
    }
}

void MainWindow::on_button_show_rooms_clicked()
{
    connect(ui->button_show_rooms, SIGNAL(clicked()), show_rooms_button, SLOT(show()));
    show_rooms_button->showFullScreen();
}

void MainWindow::on_show_database_clicked()
{
    connect(ui->show_database, SIGNAL(clicked()), show_database_button, SLOT(show()));
    show_database_button->showFullScreen();
}

void MainWindow::on_button_add_client_clicked()
{
    connect(ui->button_add_client, SIGNAL(clicked()), add_client_button, SLOT(show()));
    add_client_button->showNormal();
}
