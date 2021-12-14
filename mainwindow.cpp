#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "popfromdatabase.h"

PGconn *conn;                   // Интерфейс между БД и С-программой
QString gl__table_name;         // Костыль, чтобы передать имя таблицы во вторую форму


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    char conn_info[CONN_LIMIT];                      // Строка, содержащая параметры авторизации
    extern QString gl__table_name;
    extern PGconn *conn;


    // Тут записываем данные из формы авторизации в объекты типа QString
    QString user_name       = ui->user_name->text();
    QString data_base_name  = ui->data_base_name->text();
    QString table_name      = ui->table_name->text();

    // Костыль, чтобы передать имя таблицы во вторую форму
    gl__table_name = table_name;

    // Подготавливаем строку с данными авторизации и передаем её в ф-цию подключения к бд
    sprintf(conn_info, "user=%s dbname=%s", user_name.toStdString().c_str(), data_base_name.toStdString().c_str());
    conn = PQconnectdb(conn_info);

    // Ошибка подключения
    if (PQstatus(conn) == CONNECTION_BAD) {
        ui->statusbar->showMessage(PQerrorMessage(conn));
        PQfinish(conn);
    }
    // Подключение установлено
    else {
        ui->statusbar->showMessage("Connection completed!");
        // Открытие второго окна
        PopFromDataBase window;
        window.setModal(true);
        window.exec();
    }

}
