/************************ Includes **************************/
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "bms-rx-data.h"


/************************ Variables **************************/
bool isStopRequestedByUser = false;

/************************ Functions **************************/
int main()
{
    signal(SIGINT, sighandler);

    BMSDataReceiveFromConsole();
    return 0;
}
