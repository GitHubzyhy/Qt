#include "thread.h"
#include<iostream>
void Thread::run()
{
    while (1)
    {

        std::string isQ;
        std::cin>>isQ;
        if (isQ.compare("Q")==0) break;
    }
}
