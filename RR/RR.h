#ifndef RR_H
#define RR_H

#include "process.h"

Processes GetProcesses(FILE *fp);
void RR(FILE *out, Processes processes, unsigned quantum, double delaySec);

#endif
