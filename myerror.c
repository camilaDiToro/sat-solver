
#include <stdio.h>
#include <stdlib.h>
#include "myerror.h"

void perrorexit(char * fname)
{
    perror(fname);
    exit(EXIT_FAILURE);
}