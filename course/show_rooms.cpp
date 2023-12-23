#include "show_rooms.h"
#include "ui_show_rooms.h"

show_rooms::show_rooms(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::show_rooms)
{
    ui->setupUi(this);

    db_rooms = QSqlDatabase::addDatabase("QSQLITE");
    db_rooms.setDatabaseName("./../SQLiteStudio");
    if(db_rooms.open()){
        qDebug() << "База данных открыта!";
    }
    else{
        qDebug() << "Проблема с открытием!";
    }

    ui->pages_rooms->setCurrentIndex(0);

    for (int pageIndex = 0; pageIndex < ui->pages_rooms->count(); ++pageIndex) {
        QSqlQuery query;
        query.prepare("SELECT * FROM computer_club_rooms WHERE id = :id");
        query.bindValue(":id", pageIndex);

        if(query.exec() && query.next()) {
            QString pictureData = query.value("picture_room").toString();
            QByteArray description = query.value("description").toByteArray();
            QByteArray price = query.value("price_for_hour").toByteArray();

            QLabel *imageLabel = ui->pages_rooms->widget(pageIndex)->findChild<QLabel *>("imageLabel" + QString::number(pageIndex));
            QTextBrowser *descriptionBrowser = ui->pages_rooms->widget(pageIndex)->findChild<QTextBrowser *>("descriptionBrowser" + QString::number(pageIndex));
            QTextBrowser *priceBrowser = ui->pages_rooms->widget(pageIndex)->findChild<QTextBrowser *>("priceBrowser" + QString::number(pageIndex));

            if (imageLabel && descriptionBrowser && priceBrowser) {
                QPixmap image;
                image.load(pictureData);
                imageLabel->setPixmap(image);
                descriptionBrowser->setText(description);
                priceBrowser->setText(price);
            }
        }
    }
    //db_rooms.close();
    //QSqlDatabase::removeDatabase("connection1");
}

show_rooms::~show_rooms()
{
    db_rooms.close();
    delete ui;
}

void show_rooms::on_next_page1_clicked()
{
    ui->pages_rooms->setCurrentIndex(1);
}

void show_rooms::on_next_page2_clicked()
{
    ui->pages_rooms->setCurrentIndex(2);
}


void show_rooms::on_next_page3_clicked()
{
    ui->pages_rooms->setCurrentIndex(3);
}

void show_rooms::on_next_page4_clicked()
{
    ui->pages_rooms->setCurrentIndex(0);
}

void show_rooms::on_previos_page4_clicked()
{
    ui->pages_rooms->setCurrentIndex(3);
}

void show_rooms::on_previos_page1_clicked()
{
    ui->pages_rooms->setCurrentIndex(0);
}

void show_rooms::on_previos_page2_clicked()
{
    ui->pages_rooms->setCurrentIndex(1);
}


void show_rooms::on_previos_page3_clicked()
{
    ui->pages_rooms->setCurrentIndex(2);
}

void show_rooms::on_stop_showing_clicked()
{
    QWidget::close();
}
