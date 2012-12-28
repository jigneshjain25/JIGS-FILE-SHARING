#include "myinitthread.h"

MyInitThread::MyInitThread()
{
    protected:
    void start()
    {
        run();
    }

    void run()
    {
            /* Do whatever needs to be done to init your application! */
       QThread::msleep(5000); //Sleep 5 sec to simulate work ;-)
    }
}
