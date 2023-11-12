#include "startdialog_kuzmenok_denis.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartDialog_Kuzmenok_Denis startDialog;
    startDialog.show();

    return a.exec();
}
