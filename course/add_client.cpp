#include "add_client.h"
#include "ui_add_client.h"

add_client::add_client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_client)
{

    ui->setupUi(this);


    int initialIndex = ui->chosen_room->findText("Выберите комнату");
    QListView *listView = qobject_cast<QListView*>(ui->chosen_room->view());
    if (listView) {
        listView->setRowHidden(initialIndex, true);
    }

    button_cal = new calculator();
    connect(ui->check_price, SIGNAL(clicked()), button_cal, SLOT(show()));

    QRegExp rx("[а-яА-Я]{2,}\\s[а-яА-Я]{2,}\\s[а-яА-Я]{2,}");
    QRegExpValidator *validator = new QRegExpValidator(rx, this);
    ui->name_client->setValidator(validator);

    QDateTime ds = QDateTime::currentDateTime();
    ui->data_start->setDateTime(ds);
    QDateTime de = QDateTime::currentDateTime();
    ui->data_end->setDateTime(de);

    ui->status->setReadOnly(true);
    ui->price_hour->setReadOnly(true);
    ui->total_price->setReadOnly(true);
}

add_client::~add_client()
{
    delete ui;
}


void add_client::on_button_load_clicked()
{
    QString filename = QFileDialog::getOpenFileName(nullptr, "Выберите изображение", QDir::currentPath(), "*.png *.jpg *.jpeg");
    QImage image(filename);
    QPixmap temp(filename);
    int width = ui->photo->width();
    int height = ui->photo->height();

    if (!image.isNull()) {
        ui->photo->setPixmap(temp.scaled(width, height, Qt::KeepAspectRatio));
    }
    else {
           QMessageBox::warning(this, "Ошибка", "Не удалось загрузить изображение.");
       }
}


void add_client::on_button_exit_sec_clicked()
{
    db_rooms_price.close();
    QWidget::close();
}



void add_client::on_check_FIO_clicked()
{
    QRegExp rx("[а-яА-Я]{2,}\\s[а-яА-Я]{2,}\\s[а-яА-Я]{2,}");
    QRegExpValidator *validator = new QRegExpValidator(rx, this);
    ui->name_client->setValidator(validator);
    QString text = ui->name_client->text();
    if(ui->name_client->text().isEmpty()){
        QMessageBox::information(this,"Ошибка ввода","Введите ФИО");
        ui->check_FIO->setChecked(false);
        return;
    }
    if(!rx.exactMatch(text)){
        QMessageBox::critical(this, "Ошибка", "Неправильно введено ФИО");
        ui->check_FIO->setChecked(false);
        ui->name_client->clear();
        ui->name_client->setFocus();
        return;
    }
    ui->check_FIO->setEnabled(false);
}


void add_client::on_button_reset_clicked()
{
    QDateTime ds = QDateTime::currentDateTime();
    QDateTime de = QDateTime::currentDateTime();
    ui->check_FIO->setChecked(false);
    ui->check_add->setChecked(false);
    ui->photo->clear();
    ui->name_client->clear();
    ui->data_start->setDateTime(ds);
    ui->data_end->setDateTime(de);
    ui->chosen_room->insertItem(0, "Выберите комнату");
    int initialIndex = ui->chosen_room->findText("Выберите комнату");
    ui->chosen_room->setCurrentIndex(initialIndex);
    QListView *listView = qobject_cast<QListView*>(ui->chosen_room->view());
        if (listView) {
            listView->setRowHidden(initialIndex, true);
        }
    ui->status->clear();
    ui->price_hour->clear();
    ui->total_price->clear();
    ui->check_add->setEnabled(true);
    ui->button_load->setEnabled(true);
    ui->name_client->setReadOnly(false);
    ui->data_start->setReadOnly(false);
    ui->data_end->setReadOnly(false);
    ui->chosen_room->setEnabled(true);
    ui->check_FIO->setEnabled(true);
}

void add_client::on_check_add_clicked()
{
    QDateTime time_start = ui->data_start->dateTime();
    QDateTime time_end = ui->data_end->dateTime();
    QDateTime now = QDateTime::currentDateTime();
    db_rooms_price = QSqlDatabase::addDatabase("QSQLITE");
    db_rooms_price.setDatabaseName("./../SQLiteStudio");

    if(db_rooms_price.open()){
        QSqlQuery query;
        query.prepare("SELECT price_for_hour FROM computer_club_rooms WHERE id = :id");
        query.bindValue(":id", ui->chosen_room->currentText().toInt() - 1);
        if (query.exec() && query.next()) {
            QString price = query.value("price_for_hour").toString();
            ui->price_hour->setText(price);

            QString temp = price;
            temp.chop(7);
            double pricePerHour = temp.toDouble();
            qint64 seconds = time_start.secsTo(time_end);

            double minuts = seconds / 60;
            double pricePerMinuts = pricePerHour / 60;
            double cost = minuts * pricePerMinuts;
            ui->total_price->setText(QString::number(cost));
        }
        else {
            QMessageBox::warning(this,"Ошибка базы данных","Ошибка выполнения запроса.");
        }
    }
    else {
        QMessageBox::warning(this,"Ошибка базы данных","Ошибка открытия базы данных.");
    }
    //db_rooms_price.close();
    //QSqlDatabase::removeDatabase("connection2");

    if (time_start == time_end || ui->chosen_room->currentText() == "Выберите комнату") {
        ui->status->setText("");
    } else if (time_start > now && time_end > now) {
        ui->status->setText("В брони");
    } else if (time_start <= now && time_end >= now) {
        ui->status->setText("Клиент играет");
    } else if (time_start < now && time_end < now) {
        ui->status->setText("Игровой процесс завершён");
    }
    if((ui->check_FIO->isChecked()) && (time_start < time_end) && (ui->chosen_room->currentText() != "Выберите комнату") && (!ui->status->text().isEmpty()) && (!ui->total_price->text().isEmpty()) && (ui->photo->pixmap())){
        QMessageBox::information(this, "Поле ввода", "Вы успешно создали заявку!");
        ui->check_add->setEnabled(false);
        ui->button_load->setEnabled(false);
        ui->name_client->setReadOnly(true);
        ui->data_start->setReadOnly(true);
        ui->data_end->setReadOnly(true);
        ui->chosen_room->setEnabled(false);
        ui->status->setReadOnly(true);
        ui->price_hour->setReadOnly(true);
        ui->total_price->setReadOnly(true);
        ui->check_FIO->setEnabled(false);
    }
    else{
        QMessageBox::warning(this, "Поле ввода", "Некорректный ввод в поля заявки!");
        ui->check_add->setChecked(false);
        if(!ui->check_FIO->isChecked()){
            QMessageBox::information(this, "Поле ввода", "Введите ФИО клиента!");
        }
        else if(time_start >= time_end){
            QMessageBox::information(this, "Поле ввода", "Некорректная дата ухода клиента!");
            ui->status->setText("");
        }
        else if(ui->chosen_room->currentText() == "Выберите комнату"){
            QMessageBox::information(this, "Поле ввода", "Выберите комнату!");
        }
        else if(!ui->photo->pixmap()){
            QMessageBox::information(this, "Поле ввода", "Нет фотографии клиента!");
        }
    }
}

void add_client::on_button_save_clicked()
{
    if(ui->check_add->isChecked()){
        db_add_client = QSqlDatabase::addDatabase("QSQLITE");
        db_add_client.setDatabaseName("./../SQLiteStudio");
        if (db_add_client.open()) {
            qDebug() << "Установлено подключение к базе данных";
        } else {
            qDebug() << "Ошибка открытия базы данных";
            qDebug() << "Ошибка: " << db_add_client.lastError().text();
        }
        QString name = ui->name_client->text();
        QString data1 = ui->data_start->dateTime().toString();
        QString data2 = ui->data_end->dateTime().toString();
        int comboBoxValue = ui->chosen_room->currentText().toInt();
        QString client_status = ui->status->text();
        QString price_for_hour_text = ui->price_hour->text();
        double total_client_price = ui->total_price->text().toDouble();
        QLabel *label = ui->photo;

        QByteArray byteArray;
        const QPixmap *pixMapPointer = label->pixmap();
        if(pixMapPointer != nullptr){
            QPixmap pixMap = *pixMapPointer;
            QBuffer buffer(&byteArray);
            buffer.open(QIODevice::WriteOnly);
            pixMap.save(&buffer, "PNG");
        }

        QSqlQuery query;
        query.prepare("INSERT INTO clients(picture, fio, date_start, date_end, room, status, price_hour, price) VALUES(:image, :fio_client, :date_start_1, :date_end_2, :room_client, :status_client, :temp_price, :total_price)");

        query.bindValue(":image", byteArray);
        query.bindValue(":fio_client", name);
        query.bindValue(":date_start_1", data1);
        query.bindValue(":date_end_2", data2);
        query.bindValue(":room_client", comboBoxValue);
        query.bindValue(":status_client", client_status);
        query.bindValue(":temp_price", price_for_hour_text);
        query.bindValue(":total_price", total_client_price);

        if(query.exec()) {
            qDebug() << "Установлено подключение к базе данных";
        }
        else {
            qDebug() << "Ошибка: " << query.lastError().text();
        }
        QMessageBox::information(this, "Создание заявки", "Вы успешно вписали клиента!");
        this->close();
        on_button_reset_clicked();
    }
    else{
        //QMessageBox::information(this, "Создание заявки", "Сначала поставьте галочку в поле 'Все поля заполнены верно'.");
        return;
    }
}


void add_client::on_edit_clicked()
{
    if(ui->check_add->isChecked()){
        ui->check_add->setChecked(false);
        ui->check_add->setEnabled(true);
        ui->button_load->setEnabled(true);
        ui->name_client->setReadOnly(false);
        ui->data_start->setReadOnly(false);
        ui->data_end->setReadOnly(false);
        ui->chosen_room->setEnabled(true);
        ui->check_FIO->setEnabled(true);
        ui->check_FIO->setChecked(false);
        return;
    }
    else{
        //QMessageBox::information(this, "Редактирование", "Вы и так можете сейчас изменить заявку.");
        return;
    }
}

void add_client::slot(QString name, QString client_status, QDateTime date_start, QDateTime date_end, QString price_for_hour, int total_price, int number_room, QPixmap image_client)
{

    ui->name_client->setText(name);
    ui->data_start->setDateTime(date_start);
    ui->chosen_room->setCurrentIndex(number_room);
    ui->data_end->setDateTime(date_end);
    ui->status->setText(client_status);
    ui->price_hour->setText(price_for_hour);
    ui->total_price->setText(QString::number(total_price));
    ui->photo->setPixmap(image_client);


    ui->check_FIO->setChecked(true);
    ui->check_FIO->setEnabled(false);
    ui->check_add->setChecked(true);
    ui->check_add->setEnabled(false);
    ui->button_load->setEnabled(false);
    ui->name_client->setReadOnly(true);
    ui->data_start->setReadOnly(true);
    ui->data_end->setReadOnly(true);
    ui->chosen_room->setEnabled(false);
    ui->status->setReadOnly(true);
    ui->price_hour->setReadOnly(true);
    ui->total_price->setReadOnly(true);
    ui->button_exit_sec->hide();

    //event = new QCloseEvent;
    //event->ignore();

    connect(ui->edit, &QPushButton::clicked, this, &add_client::on_edit_clicked);
    connect(ui->button_reset, &QPushButton::clicked, this, &add_client::on_button_reset_clicked);
    connect(ui->button_save, &QPushButton::clicked, this, &add_client::on_button_save_clicked);
}
