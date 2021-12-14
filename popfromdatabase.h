#ifndef POPFROMDATABASE_H
#define POPFROMDATABASE_H

#include <QDialog>
#include <stdio.h>
#include <stdlib.h>
#include "/usr/include/postgresql/libpq-fe.h"
#include <QTextEdit>

#define CONN_LIMIT      40
#define FORMAT_LIMIT    100



namespace Ui {
class PopFromDataBase;
}

class PopFromDataBase : public QDialog
{
    Q_OBJECT

public:
    explicit PopFromDataBase(QWidget *parent = nullptr);
    ~PopFromDataBase();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::PopFromDataBase *ui;
};

#endif // POPFROMDATABASE_H
