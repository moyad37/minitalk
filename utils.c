#include "client_bonus.h"

void get_recived(int s)
{
    if(s == SIGUSR1)
        write(1, "resived SIGUSR1\n", 16);
    else if (s == SIGUSR2)
        write(1, "resived SIGUSR2\n", 16);
    else
        write(2, "Error by resive Signals\n", 24);
}