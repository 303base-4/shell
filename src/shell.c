#include "shell.h"
#include "log.h"
#include <assert.h>

log_t Log;

static void free_arg(int argc, char **argv) // 该子程序用于释放argv分配的内存
{
    for (int i = 0; i < argc; i++)
    {
        free(argv[i]);
    }
    free(argv);
}
static void cd(const char *buffer, int argc, char **argv) // 该子程序用于实现cd命令
{
    log_push(&Log, buffer);
    assert(argc <= 2);
    chdir(argv[1]);
    free_arg(argc, argv);
}
static void exit_shell(const char *buffer, int argc, char **argv) // 该子程序用于实现exit命令
{
    log_push(&Log, buffer);
    free_arg(argc, argv);
}
static void hist(const char *buffer, int argc, char **argv) // 该子程序用于实现!#命令
{
    node *p = Log.head;
    while (p != NULL)
    {
        printf("%s\n", p->cmd);
        p = p->next;
    }
    free_arg(argc, argv);
}
static void redo(const char *buffer, int argc, char **argv) // 该子程序用于实现!prefix命令
{
    char *cmd = log_search(&Log, argv[0] + 1);
    if (cmd == NULL)
    {
        printf("No Match\n");
    }
    else
    {
        execute(cmd);
    }
    free_arg(argc, argv);
}
static void ls(const char *buffer, int argc, char **argv) // 该子程序用于实现ls命令
{
    log_push(&Log, argv[0]);
    system("ls");
    free_arg(argc, argv);
}
/**
 * shell的入口
 */
void prefix()
{
    char *cwd;
    cwd = getcwd(NULL, 0);
    printf("%s$", cwd);
    free(cwd);
}

int execute(char *buffer)
{
    // 解析buffer。以空格、制表符和回车符作为分隔符，将buffer解析为命令和参数。
    // 解析后的存储格式类似于int main(int argc,char *argv[])函数的参数
    // 其中argc用于存储参数总数，字符串数组argv[]用于存储参数。按照惯例，argv[0]应为命令本身。
    int argc = 0;
    char **argv = (char **)malloc(sizeof(char *));
    for (int i = 0; i < strlen(buffer); i++)
    {
        if (buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n')
            continue;
        argv = (char **)realloc(argv, (argc + 1) * sizeof(char *));
        argv[argc] = (char *)malloc(sizeof(char));
        int cnt = 0;
        while (buffer[i] != ' ' && i < strlen(buffer))
        {
            argv[argc] = (char *)realloc(argv[argc], (cnt + 2) * sizeof(char));
            argv[argc][cnt++] = buffer[i++];
        }
        argv[argc][cnt] = '\0';
        argc++;
    }
    // 根据解析后的参数调用相应子程序实现内部命令
    if (strcmp(argv[0], "cd") == 0)
    {
        cd(buffer, argc, argv);
        return 1;
    }
    if (strcmp(argv[0], "exit") == 0)
    {
        exit_shell(buffer, argc, argv);
        return 0;
    }
    if (strcmp(argv[0], "!#") == 0)
    {
        hist(buffer, argc, argv);
        return 1;
    }
    if (argv[0][0] == '!')
    {
        redo(buffer, argc, argv);
        return 1;
    }
    if (strcmp(argv[0], "ls") == 0)
    {
        ls(buffer, argc, argv);
        return 1;
    }
}
