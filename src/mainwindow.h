#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<vector>
#include<string>
#include<QStringList>
#include<QFileInfoList>
#include<QFileInfo>
#include<QDir>
#include<QDebug>
#include<utility>
#include<QDateTime>
#include<ctime>
#include<QTimer>
#include <thread>
#include"filefolder.h"
#include"sqlite3.h"
#include"filequery.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QStringList getFileChildrenPath(const QString &path);
    QFileInfoList getFileChildrenInfo(const QString &path);
    QFileInfoList getFolderChildrenInfo(const QString &path);
    void getAllFile(const QString &path);
    QStringList findAllMatchedPaths(const QString &str, const QString &path, int offset);
    FileFolder *addChain(const std::__cxx11::string &path, FileFolder *parent);
    int findAllMatchedPathsNum(const QString &str, const QString &path);
public slots:
    void createIndex();
    void createIndexProcess();
private slots:
    void on_lineEdit_textEdited(const QString &arg1);

    void on_verticalScrollBar_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    FileQuery * filequery;
    sqlite3 *db;
    char * errMsg;
    int resultNum;
    QString curIndexPath;
    QTimer *timer;
};

#endif // MAINWINDOW_H
