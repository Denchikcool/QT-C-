#ifndef STARTDIALOG_KUZMENOK_DENIS_H
#define STARTDIALOG_KUZMENOK_DENIS_H

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include "InputDialog_Kuzmenok_Denis.h"

class StartDialog_Kuzmenok_Denis : public QPushButton
{
    Q_OBJECT
public:
    StartDialog_Kuzmenok_Denis(QWidget * pwgt = 0);
public slots:
    void slotButtonClicked();
};

#endif // STARTDIALOG_KUZMENOK_DENIS_H
