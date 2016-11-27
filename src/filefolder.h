#ifndef FILEFOLDER_H
#define FILEFOLDER_H

#include<map>
#include<unordered_map>
#include<set>
#include<vector>
#include<string>

class FileFolder
{
public:
    FileFolder();
    FileFolder(char ch):c(ch){}
    /*
    bool operator <(const FileFolder &rhs)const
    {
        return name<rhs.name;
    }
    bool operator ==(const std::string &str)const
    {
        return name==str;
    }
    */
    char c;
    FileFolder *parent;
    std::map<char,FileFolder *> children;
};

#endif // FILEFOLDER_H
