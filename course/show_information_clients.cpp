#include "show_information_clients.h"
#include "ui_show_information_clients.h"

show_information_clients::show_information_clients(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::show_information_clients)
{
    ui->setupUi(this);
    button_add_client = new add_client();
    connect(this, &show_information_clients::signal, button_add_client, &add_client::slot);

    db_information = QSqlDatabase::addDatabase("QSQLITE");
    db_information.setDatabaseName("./../SQLiteStudio");
    if(db_information.open()){
        qDebug() << "База данных по клиентам успешно открыта!";

        model = new QSqlTableModel(this, db_information);
        model->setTable("clients");
        model->select();

        model->setHeaderData(0, Qt::Horizontal, "ID", Qt::DisplayRole);
        model->setHeaderData(1, Qt::Horizontal, "Фотография", Qt::DisplayRole);
        model->setHeaderData(2, Qt::Horizontal, "Фамилия Имя Отчество", Qt::DisplayRole);
        model->setHeaderData(3, Qt::Horizontal, "Дата начала игрового процесса", Qt::DisplayRole);
        model->setHeaderData(4, Qt::Horizontal, "Дата окончания игрового процесса", Qt::DisplayRole);
        model->setHeaderData(5, Qt::Horizontal, "Комната", Qt::DisplayRole);
        model->setHeaderData(6, Qt::Horizontal, "Статус", Qt::DisplayRole);
        model->setHeaderData(7, Qt::Horizontal, "Цена за час", Qt::DisplayRole);
        model->setHeaderData(8, Qt::Horizontal, "Итого к оплате", Qt::DisplayRole);

        ui->clients_table->setModel(model);
        ui->clients_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->clients_table->setColumnHidden(0, true);
        ui->clients_table->setColumnHidden(1, true);
        ui->clients_table->setColumnHidden(7, true);
        ui->clients_table->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->clients_table->setSortingEnabled(true);

        QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(parent);
        proxyModel->setSourceModel(model);
        ui->clients_table->setModel(proxyModel);
        QLineEdit *lineEdit = new QLineEdit;
        lineEdit = ui->line_search;
        QObject::connect(lineEdit, &QLineEdit::textChanged, [proxyModel](const QString &text){
            QRegExp regExp(text, Qt::CaseInsensitive, QRegExp::Wildcard);
            proxyModel->setFilterRegExp(regExp);
            proxyModel->setFilterKeyColumn(2);
        });
    }
    else{
        qDebug() << "Возникли проблемы при открытии базы данных клиентов.";
    }
    //connect(ui->clients_table, SIGNAL(clicked(const QModelIndex &)), this, SLOT(add_client(const QModelIndex &)));
}

show_information_clients::~show_information_clients()
{
    db_information.close();
    delete ui;
}

void show_information_clients::on_exit_from_db_clicked()
{
    this->close();
}

void show_information_clients::on_remove_client_clicked()
{
    model->removeRow(currentRow);
    model->select();
}

void show_information_clients::on_clients_table_clicked(const QModelIndex &index)
{
    currentRow = index.row();
    QModelIndex columnIndexZero = ui->clients_table->model()->index(currentRow, 0);  // Получаем индекс для нулевого столбца текущей строки
    QVariant data = ui->clients_table->model()->data(columnIndexZero);  // Получаем значение из нулевого столбца
    idColumn = data.toInt();
}

void show_information_clients::on_refresh_data_clicked()
{
    model->select();
    ui->clients_table->selectRow(currentRow);
}

/*void show_information_clients::on_clients_table_doubleClicked(const QModelIndex &index)
{

}*/

/*void show_information_clients::on_find_button_clicked()
{
    QString fio_to_find;
    int room_to_find;
    ui->check_room->setEnabled(true);
    ui->check_fio->setEnabled(true);
    if(ui->check_room->isChecked() && ui->check_fio->isChecked()){
        ui->check_fio->setChecked(false);
        ui->check_room->setChecked(false);
        QMessageBox::critical(this, "Поиск по базе данных", "Нельзя совершить поиск сразу по двум параметрам!");
        return;
    }
    else if(ui->check_fio->isChecked()){
        ui->check_room->setEnabled(false);
        fio_to_find = ui->line_search->text();
        model->setFilter(QString("fio='%1'").arg(fio_to_find));
        if(fio_to_find == 0){
            model->setFilter("");
            model->select();
            ui->check_room->setEnabled(true);
            ui->check_fio->setEnabled(true);
            ui->check_fio->setChecked(false);
            ui->check_room->setChecked(false);
        }
    }
    else if(ui->check_room->isChecked()){
        ui->check_fio->setEnabled(false);
        room_to_find = ui->line_search->text().toInt();
        model->setFilter(QString("Room='%1'").arg(room_to_find));
        if(room_to_find == 0){
            model->setFilter("");
            model->select();
            ui->check_room->setEnabled(true);
            ui->check_fio->setEnabled(true);
            ui->check_fio->setChecked(false);
            ui->check_room->setChecked(false);
        }
    }
    else{
        ui->line_search->clear();
        QMessageBox::warning(this, "Поиск по базе данных", "Выберите по какому критерию вы хотите найти записи!");
        return;
    }
}*/

void show_information_clients::on_edit_data_clicked()
{
    if(currentRow >= 0){
        QSqlQuery query;
        query.prepare("SELECT * FROM clients WHERE id=:id");
        query.bindValue(":id", idColumn);

        if(query.exec() && query.next()){
            QString name_client = query.value("fio").toString();
            QString date_string_1 = query.value("date_start").toString();
            QString date_string_2 = query.value("date_end").toString();
            QDateTime date1 = QDateTime::fromString(date_string_1, "ddd MMM d HH:mm:ss yyyy");
            QDateTime date2 = QDateTime::fromString(date_string_2, "ddd MMM d HH:mm:ss yyyy");
            int room_client = query.value("room").toInt();
            QString price_for_hour = query.value("price_hour").toString();
            QString status_client = query.value("status").toString();
            double total_price = query.value("price").toDouble();
            QByteArray client_image_data = query.value("picture").toByteArray();
            QPixmap client_image;
            client_image.loadFromData(client_image_data);

            connect(ui->edit_data, SIGNAL(clicked()), button_add_client, SLOT(show()));

            button_add_client->showNormal();
            emit signal(name_client, status_client, date1, date2, price_for_hour, total_price, room_client, client_image);

        }
        on_remove_client_clicked();
    }
}
