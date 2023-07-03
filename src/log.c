/** @file log.c */
#include <stdlib.h>
#include <string.h>
#include "log.h"

/**
对log进行初始化，log的“构造函数”
 */

void log_init(log_t *l) 
{
    l=(log_t*)malloc(sizeof(log_t));
    l->head=NULL;
}

/**
销毁一个log，释放所有内存空间，log的“析构函数”
 */

void log_destroy(log_t* l) 
{
    node *pre=l->head,*p=pre->next;
    while(p!=NULL)
    {
        free(pre);
        pre=p;
        p=pre->next;
    }
    free(pre);
    free(l);
}

/**
向log中推入一个字符串，你可以将log视为一个由链表组成的栈
 */

void log_push(log_t* l, const char *item) 
{
    if(l->head==NULL)
    {
        l->head=(node*)malloc(sizeof(node));
        strcpy(l->head->cmd,item);
    }
    else
    {
        node *s,*r;
        r=l->head;
        while(r->next!=NULL)
        {
            r=r->next;
        }
        s=(node*)malloc(sizeof(node));
        strcpy(s->cmd,item);
        r->next=s;
        r=s;
        r->next=NULL;
    }
}


/**
搜索log中是否含有对应前缀的字符串
 */

char *log_search(log_t* l, const char *prefix) 
{
    const char s[2]=" ";
    int i=1;
    node *p=l->head;
    while(p!=NULL&&strtok(p->cmd,s)!=prefix)
    {
        p=p->next;
        i++;
    }
    char *tmp=p->cmd;
    if(p==NULL)
        return NULL;
    else
        return tmp;
}
