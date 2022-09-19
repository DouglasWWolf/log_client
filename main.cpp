#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "log.h"

CLog Log;

int main()
{
    Log.init(5000);

    for (int i=0; i<100; ++i)
    {
        Log.printf("This is log data #%d\n", i+1);
        usleep(10000);
    }


}
