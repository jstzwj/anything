#ifndef FILEQUERY_H
#define FILEQUERY_H

#include<QThread>
#include<QStringList>
#include<QString>
#include<QDebug>
#include<QFileInfoList>
#include<QFileInfo>
#include<QDateTime>
#include<QDir>
#include<QScrollBar>
#include"sqlite3.h"
class FileQuery: public QThread
{
    Q_OBJECT
public:
    sqlite3 *db;
    char * errMsg;
    QScrollBar * scbar;
    FileQuery();

    QStringList findAllMatchedPaths(sqlite3 *db, const QString &str, const QString &path, int offset);
    int findAllMatchedPathsNum(sqlite3 *db, const QString &str, const QString &path);

    QStringList getFileChildrenPath(const QString &path);
    QFileInfoList getFileChildrenInfo(const QString &path);
    QFileInfoList getFolderChildrenInfo(const QString &path);
    void getAllFile(const QString &path);

 protected:
    void run();

};
#endif // FILEQUERY_H
