#ifndef INPUTDIALOG_KUZMENOK_DENIS_H
#define INPUTDIALOG_KUZMENOK_DENIS_H

#include <QDialog>
#include <QLineEdit>

class InputDialog_Kuzmenok_Denis : public QDialog
{
    Q_OBJECT
private:
    QLineEdit * m_ptxtFirstName;
    QLineEdit * m_ptxtLastName;
public:
    InputDialog_Kuzmenok_Denis(QWidget* pwgt = 0);

    QString firstName() const;
    QString lastName() const;
};

#endif // INPUTDIALOG_KUZMENOK_DENIS_H
