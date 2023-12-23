#include "mainwindow.h"
#include "adminlogin.h"
#include <QApplication>
#include <QFile>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file (":/style.css");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(file.readAll());
    MainWindow *w = new MainWindow();
    adminLogin *al = new adminLogin(w);
    al->setFixedSize(QApplication::desktop()->screen()->width(),QApplication::desktop()->screen()->height());
    al->showFullScreen();

    return a.exec();
}
