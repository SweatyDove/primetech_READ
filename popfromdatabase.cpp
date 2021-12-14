#include "popfromdatabase.h"
#include "ui_popfromdatabase.h"


PopFromDataBase::PopFromDataBase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PopFromDataBase)
{
    ui->setupUi(this);
}

PopFromDataBase::~PopFromDataBase()
{
    delete ui;
}


// Кнопка вывода всего содержимого таблицы БД
void PopFromDataBase::on_pushButton_clicked()
{

    extern QString gl__table_name;
    extern PGconn *conn;

    PGresult *res = nullptr;

    int rows_num = 0;                       // Число строк
    int i = 0;
    char format_str[FORMAT_LIMIT];          // Строка форматированного ввода


    // Запрашиваем все строки из таблицы
    sprintf(format_str, "SELECT * FROM %s", gl__table_name.toStdString().c_str());
    res = PQexec(conn, format_str);
    // Ошибка запроса
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        ui->textBrowser->append(PQerrorMessage(conn));
    }
    //
    else {
        rows_num = PQntuples(res);                     // Определяем число строк, к-е вернул запрос
        ui->textBrowser->append("\nPrinting all:");
        // Вывод строк
        for (i = 0; i < rows_num; i++) {
            sprintf(format_str, "%s %s", PQgetvalue(res, i, 0), PQgetvalue(res, i, 1));
            ui->textBrowser->append(format_str);
        }
    }

}

// Кнопка вывода строки с определенным Id
void PopFromDataBase::on_pushButton_3_clicked()
{

    extern QString gl__table_name;
    extern PGconn *conn;
    PGresult *res = nullptr;

    char format_str[FORMAT_LIMIT];

    // Считываем Id строки, к-ю нужно вывести
    QString row_id = ui->certain_id->text();
    int id = row_id.toInt();

    // Запрос к БД на вывод строки
    sprintf(format_str, "SELECT * FROM %s WHERE id=%d", gl__table_name.toStdString().c_str(), id);
    res = PQexec(conn, format_str);
    // Ошибка запроса
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        ui->textBrowser->append(PQerrorMessage(conn));
    }
    // Вывод запрошенной строки
    sprintf(format_str, "\nPrint row with Id = %d:", id);
    ui->textBrowser->append(format_str);
    sprintf(format_str, "%s %s", PQgetvalue(res, 0, 0), PQgetvalue(res, 0, 1));
    ui->textBrowser->append(format_str);

}


// Кнопка вывода строк в определенном диапазоне
void PopFromDataBase::on_pushButton_4_clicked()
{
    extern QString gl__table_name;
    extern PGconn *conn;


    int i = 0;
    char format_str[FORMAT_LIMIT];
    PGresult *res = nullptr;



    // Считываем значения из полей (left/right id) и записываем их в объекты типа QString.
    QString left_row_id = ui->left_id->text();
    QString right_row_id = ui->right_id->text();
    int l_id = left_row_id.toInt();
    int r_id = right_row_id.toInt();

    // Запрос к БД на вывод строк в указанном диапазоне
    sprintf(format_str, "SELECT * FROM %s WHERE id>=%d AND id<=%d", gl__table_name.toStdString().c_str(), l_id, r_id);
    res = PQexec(conn, format_str);
    // Ошибка запроса
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        ui->textBrowser->append(PQerrorMessage(conn));
    }
    // Вывод строк
    sprintf(format_str, "\nPrint row with (id >= %d && id <= %d)", l_id, r_id);
    ui->textBrowser->append(format_str);
    for (i = 0 ; i <= r_id - l_id; i++) {
        sprintf(format_str, "%s %s", PQgetvalue(res, i, 0), PQgetvalue(res, i, 1));
        ui->textBrowser->append(format_str);
    }

}
