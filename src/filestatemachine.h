#ifndef FILESTATEMACHINE_H
#define FILESTATEMACHINE_H

#include<map>
class FileStateMachine
{
public:
    FileStateMachine();
    std::map<char16_t,std::map<char16_t,int> > data;
};

#endif // FILESTATEMACHINE_H
