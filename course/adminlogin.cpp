#include "adminlogin.h"
#include "ui_adminlogin.h"

#include <QMessageBox>
#include <QDesktopWidget>

adminLogin::adminLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminLogin)
{
    ui->setupUi(this);

    int x = QApplication::desktop()->screen()->width()/2 - ui->groupBox->width()/2;
    int y = QApplication::desktop()->screen()->height()/2 - ui->groupBox->height()/2;
    ui->groupBox->move(x,y);
}

adminLogin::~adminLogin()
{
    delete ui;
}


void adminLogin::on_exitButton_clicked()
{
    this->close();
    parentWidget()->close();
}

void adminLogin::on_loginButton_clicked()
{
    if(ui->usernameEdit->text().trimmed().isEmpty() || ui->passwordEdit->text().isEmpty()){
        QMessageBox::information(this,"Вход администратора","Введите свое имя пользователя и пароль");
        ui->usernameEdit->setFocus();
        return;
    }
    if(ui->usernameEdit->text() != "denchik_cool" || ui->passwordEdit->text() != "170203"){
        QMessageBox::warning(this,"Вход администратора","Неверное имя пользователя или пароль");
        ui->passwordEdit->clear();
        ui->usernameEdit->setFocus();
        return;
    }

    ui->loginButton->setFocus();
    this->close();
    parentWidget()->setFixedSize(QApplication::desktop()->screen()->width(),QApplication::desktop()->screen()->height());
    parentWidget()->showFullScreen();
}
