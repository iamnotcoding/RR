#ifndef PRINT_ERR_H
#define PRINT_ERR_H

#include <stdio.h>

#define PRINT_ERR(msg) fprintf(stderr, "%s %s() line : %d %s\n", __FILE__, __func__, __LINE__, msg);

#endif 
