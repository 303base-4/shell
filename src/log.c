/** @file log.c */
#include "log.h"
#include <stdlib.h>
#include <string.h>

/**
对log进行初始化，log的“构造函数”
 */

void log_init(log_t *l)
{
    l->head = NULL;
}

/**
����һ��log���ͷ������ڴ�ռ䣬log�ġ�����������
 */

void log_destroy(log_t *l)
{
    node *p, *p1;
    p1 = l->head;
    p = p1->next;
    while (p != NULL)
    {
        free(p1->cmd);
        free(p1);
        p1 = p;
        p = p1->next;
    }
    free(p1->cmd);
    free(p1);
}

/**
��log������һ���ַ���������Խ�log��Ϊһ����������ɵ�ջ
 */

void log_push(log_t *l, const char *item)
{
    if (l->head == NULL)
    {
        node *p;
        p = (node *)malloc(sizeof(node));
        p->cmd = (char *)malloc((strlen(item) + 1) * sizeof(char));
        p->next = NULL;
        strcpy(p->cmd, item);
        l->head = p;
    }
    else
    {
        node *p1;
        p1 = l->head;
        while (p1->next != NULL)
        {
            p1 = p1->next;
        }
        node *p;
        p = (node *)malloc(sizeof(node));
        p->cmd = (char *)malloc((strlen(item) + 1) * sizeof(char));
        strcpy(p->cmd, item);
        p->next = p1->next;
        p1->next = p;
    }
}

/**
����log���Ƿ��ж�Ӧǰ׺���ַ���
 */

char *log_search(log_t *l, const char *prefix)
{
    char *s1 = NULL;
    node *p = l->head;
    while (p != NULL)
    {
        char *s;
        s = p->cmd;
        int i = 0, flag = 0;
        if (strlen(prefix) > strlen(s))
        {
            p = p->next;
            continue;
        }
        while (prefix[i] != '\0')
        {
            if (prefix[i] != s[i])
            {
                flag = 1;
                break;
            }
            i++;
        }
        if (flag == 0)
        {
            s1 = s;
        }
        p = p->next;
    }
    return s1;
}
