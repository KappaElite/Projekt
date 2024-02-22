#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <iostream>
using namespace std;


class MyException:public exception
{
    char *msg;
public:
    MyException(char *message): msg(message){};
    const char* what() const noexcept {
        return msg;
    }

};

#endif // MYEXCEPTION_H
