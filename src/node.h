#ifndef NODE_H
#define NODE_H

#include<map>
#include<vector>
#include"filefolder.h"
class Node
{
public:
    Node();
    char16_t c;
    std::map<char16_t,Node *> children;
    std::vector<FileFolder> files;
};

#endif // NODE_H
