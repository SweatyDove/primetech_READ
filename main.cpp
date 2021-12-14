#include "mainwindow.h"

#include <QApplication>

/* Проблемы:
 *  1) Проработать случай пустой таблицы
 *  2) Добавить status bar во вторую форму (для выводу ошибок туда, а не в общее окно)
 *  3) Обработать случаи некорректных Id-шников
 *  4) Убрать относительный путь для файла "libpq-fe.h"
 *
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
