#ifndef PROCESS_H
#define PROCESS_H

typedef struct _process
{
    unsigned time;
    unsigned pid;
    unsigned run;
    unsigned io;
    unsigned repeat;
} Process;

typedef struct _processes
{
    Process *processList;
    size_t processesNum;
} Processes;

#endif 
