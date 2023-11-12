#include "startdialog_kuzmenok_denis.h"

StartDialog_Kuzmenok_Denis::StartDialog_Kuzmenok_Denis(QWidget * pwgt): QPushButton("Нажми", pwgt)
{
    connect(this, SIGNAL(clicked()), SLOT(slotButtonClicked()));
}

void StartDialog_Kuzmenok_Denis::slotButtonClicked()
{
    InputDialog_Kuzmenok_Denis* pInputDialog = new InputDialog_Kuzmenok_Denis;
    if(pInputDialog -> exec() == QDialog::Accepted)
    {
        QMessageBox::information(
            nullptr,
            "Ваша информация:",
            "Имя:           "
            + pInputDialog -> firstName()
            + "\nФамилия:  "
            + pInputDialog -> lastName()
        );
    }
    delete pInputDialog;
}
