#include "shell.h"

log_t Log;

/**
 * shell的入口
 */
void prefix() 
{
    char s[100];
    printf("%s$",getcwd(s,sizeof(s)));
}

int execute(char* buffer) 
{
    const char s[2]=" ";
    char token[20][100];
    char *tmp;
    int i=0;
    tmp=strtok(buffer,s);
    while(tmp!=NULL)
    {
        strcpy(token[i],tmp);
        tmp=strtok(NULL,s);
        i++;
    }
    if(strcmp(token[0],"exit")==0)
    {
        return 0;
    }
    else if(strcmp(token[0],"ls")==0)
    {
        int pos=0;
        while(token[pos])
        {
            pos++;
        }
        token[pos++]=(char*)"--color=auto";
        token[pos]=NULL;
        log_push(Log,buffer);
    }
    else if(strcmp(token[0],"cd")==0)
    {
        if(token[1]!=NULL)
        {
            chdir(token[1]);
            if(chdir(token[1])==-1)
            {
                printf("No such file or directory");
            }
            continue;
        }
        log_push(Log,buffer);
    }
    
    else if(strcmp(token[0],"!#")==0)
    {
        node *p=Log->head;
        while(p!=NULL)
        {
            printf("%s",p->cmd);
            p=p->next;
        }f
        printf("\n");
    }
    else if(strcmp(token[0],"!prefix")==0)
    {
        if(log_search(buffer,prefix)==NULL)
        {
            printf("No Match\n");
        }
        execute(log_search(buffer,prefix));
    }
    return 1;
}
