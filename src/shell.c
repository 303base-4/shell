#include "shell.h"

log_t Log;

/**
 * shell的入口
 */
void prefix()
{
    char *cwd;
    cwd = getcwd(NULL, 0);
    printf("%s", cwd);
    free(cwd);
}

int execute(char *buffer)
{
}
