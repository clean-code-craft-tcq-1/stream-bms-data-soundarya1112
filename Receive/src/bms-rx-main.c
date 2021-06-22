#include <stdio.h>
#include <string.h>
#include <signal.h>
#include "bms_rx-data.h"


int main()
{
    signal(SIGINT, sighandler);

    BMSDataReceiveFromConsole();
    return 0;
}
