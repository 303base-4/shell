#ifndef __SHELL_H_
#define __SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "log.h"
#define MAX_SIZE 1000

extern log_t Log;

/**
 * Starting point for shell.
 */
void prefix();
void list_log(log_t *log);
int split(char *args[],char* str,const char* spl);
int execute(char* buffer);

#endif
