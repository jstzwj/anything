#include "filequery.h"
#include<ctime>
FileQuery::FileQuery()
{

}

void FileQuery::run()
{
    //打开数据库
    //int rc = sqlite3_open("anything.db", &db);
    //使用内存数据库
    int rc = sqlite3_open(":memory:", &db);
    if(rc)
    {
        qDebug()<<"Open database failed!\n";
    }
    else
    {
        qDebug()<<"create the database successful!\n";
    }
    //创建数据库
    sqlite3_exec(db, "CREATE table files(id INTEGER,name TEXT,path TEXT,size INTEGER,modify_time TEXT);", 0, 0, NULL);
    //寻找所有盘
    for(char c='c';c<='z';++c)
    {
        std::string name=c+std::string(":/");
        QStringList lst=getFileChildrenPath(QString(name.c_str()));
        if(!lst.isEmpty())
        {
            //开启事务
            sqlite3_exec(db, "BEGIN;", 0, 0, NULL);
            //获取每个盘下所有文件
            getAllFile(QString(name.c_str()));
            //结束事务
            sqlite3_exec(db, "COMMIT;", 0, 0, NULL);
        }
    }
}
QStringList FileQuery::findAllMatchedPaths(sqlite3 *db,const QString &str,const QString &path,int offset)
{
    QStringList result;
    //记录路径
    int nrow=0, ncolumn=0;
    char **azResult; //存放结果
    clock_t begin=clock();
    int rc=sqlite3_get_table(db,
                    ("SELECT name,path,size,modify_time from files where path LIKE \'%"+str+"%\'LIMIT 160 OFFSET "+QString::number(offset)+";").toStdString().c_str(),
                    &azResult,&nrow,&ncolumn,&errMsg); //建立表datapro
    clock_t end=clock();
    if(rc==SQLITE_OK) //查询成功
        qDebug()<<"search the table successful!\n"<<nrow<<"\ntime:"<<end-begin;
    else
        qDebug()<<errMsg;
    for(int i=0;i<nrow;++i)
    {
        result.push_back(azResult[i]);
    }
    return result;

}

int FileQuery::findAllMatchedPathsNum(sqlite3 *db,const QString &str,const QString &path)
{
    //记录路径
    int nrow=0, ncolumn=0;
    char **azResult; //存放结果
    int rc=sqlite3_get_table(db,
                    ("SELECT count(*) from files where path LIKE \'%"+str+"%\';").toStdString().c_str(),
                    &azResult,&nrow,&ncolumn,&errMsg); //建立表datapro
    if(rc==SQLITE_OK) //查询成功
        qDebug()<<"search the table successful!\n"<<"lines:"<<azResult[1];
    else
        qDebug()<<errMsg;
    return QString(azResult[1]).toInt();
}


void FileQuery::getAllFile(const QString &path)
{
    static int firstNum=0;
    static int curNum=0;
    //文件夹搜索
    QFileInfoList list=getFolderChildrenInfo(path);
    for(QFileInfo &info:list)
    {
        if(info.fileName()!="."&&info.fileName()!="..")
        {
            if(path.contains(":/"))
            {
                firstNum=list.size();
                scbar->setValue(curNum/firstNum);
                curNum++;
            }
            //记录路径
            int rc=sqlite3_exec(db,
                            ("INSERT INTO files (name,path,size,modify_time)VALUES(\'"+info.fileName()+"\',\'"+info.absoluteFilePath()+"\',"+QString::number(info.size())+",\'"+info.lastModified().toString("yyyy-MM-dd hh:mm:ss")+"\');").toStdString().c_str(),
                            0,0,&errMsg); //建立表datapro
            if(rc==SQLITE_OK) //插入成功
            {
                //qDebug()<<"insert the table successful!\n";
            }
            else
            {
                qDebug()<<errMsg;
            }
            qDebug()<<info.absoluteFilePath();
            //递归查找
            getAllFile(info.absoluteFilePath());
            //parent.children.insert(folder);
        }

    }

    //文件搜索
    list=getFileChildrenInfo(path);
    for(QFileInfo &info:list)
    {
        //记录路径
        int rc=sqlite3_exec(db,
                        ("INSERT INTO files (name,path,size,modify_time)VALUES(\'"+info.fileName()+"\',\'"+info.absoluteFilePath()+"\',"+QString::number(info.size())+",\'"+info.lastModified().toString("yyyy-MM-dd hh:mm:ss")+"\')").toStdString().c_str(),
                        0,0,&errMsg); //建立表datapro
        if(rc==SQLITE_OK) //插入成功
        {
            //qDebug()<<"insert the table successful!\n";
        }
        else
        {
            qDebug()<<errMsg;
        }
        //qDebug()<<info.absoluteFilePath();
    }
    return ;
}
QStringList FileQuery::getFileChildrenPath(const QString &path)
{
    QDir dir(path);
    if(!dir.exists())
    {
        return QStringList();
    }
    dir.setFilter(QDir::AllEntries);
    QFileInfoList list = dir.entryInfoList();

    QStringList string_list;
    for(int i=0; i<list.count();++i)
    {
        QFileInfo file_info = list.at(i);
        //QString suffix = file_info.suffix();
        //if(QString::compare(suffix, QString("png"), Qt::CaseInsensitive) == 0)
        //{
        QString absolute_file_path = file_info.absoluteFilePath();
        string_list.append(absolute_file_path);
        //}
    }
    return string_list;
}

QFileInfoList FileQuery::getFileChildrenInfo(const QString &path)
{
    QDir dir(path);
    if(!dir.exists())
    {
        return QFileInfoList();
    }
    dir.setFilter(QDir::Files);
    QFileInfoList list = dir.entryInfoList();
    return list;
}

QFileInfoList FileQuery::getFolderChildrenInfo(const QString &path)
{
    QDir dir(path);
    if(!dir.exists())
    {
        return QFileInfoList();
    }
    dir.setFilter(QDir::AllDirs);
    QFileInfoList list = dir.entryInfoList();
    return list;
}
