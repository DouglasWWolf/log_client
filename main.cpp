#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "log.h"

CLog Log1, Log2;

int main()
{
    int x1 = sizeof(sockaddr);
    int x2 = sizeof(sockaddr_in);
    int x3 = sizeof(sockaddr_in6);
    int x4 = sizeof(sockaddr_storage);

    printf("%d %d %d %d\n", x1, x2, x3, x4);

    int i;
    Log1.init(5000);
    Log2.init(5001);

    for (i=0; i<10; ++i)
    {
        Log1.printf("This is log data #%d\n", i+1);
    }

   for (i=0; i<10; ++i) Log2.printf("Log2 data");


}
