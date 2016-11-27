#include "mainwindow.h"
#include <QApplication>
#include<thread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    std::thread t(&MainWindow::createIndex,&w);
    w.show();
    int result=a.exec();
    t.join();
    return result;
}
