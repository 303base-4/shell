/** @file log.c */
#include <stdlib.h>
#include <string.h>
#include "log.h"

/**
对log进行初始化，log的“构造函数”
 */

void log_init(log_t *&l) {
	l=(log_t*)malloc(sizeof(log_t));
    l->head=NULL;
}

/**
����һ��log���ͷ������ڴ�ռ䣬log�ġ�����������
 */

void log_destroy(log_t* l) {
    node *p,*p1;
    p1=l->head;
    p=p1->next;
    while(p!=NULL){
        free(p1->cmd);
        free(p1);
        p1=p;
        p=p1->next;
    }
    free(p1->cmd);
    free(p1);
}

/**
��log������һ���ַ���������Խ�log��Ϊһ����������ɵ�ջ
 */

void log_push(log_t* l, const char *item) {
    if(l->head==NULL){
        node *p;
        p = (node*)malloc(sizeof(node));
        p->cmd=(char*)malloc(100); 
        p->next=NULL;
        strcpy(p->cmd,item);
        l->head=p;
    }
    else{
        node *p1;
        p1=l->head;
        while(p1->next!=NULL){
            p1=p1->next;
        }
        node *p;
        p = (node*)malloc(sizeof(node));
        strcpy(p->cmd,item);
        p->next=p1->next;
        p1->next=p;
    }
}


/**
����log���Ƿ��ж�Ӧǰ׺���ַ���
 */

char *log_search(log_t* l, const char *prefix) {
    node *p=l->head;
    while(p!=NULL){
        char *s;
        s=p->cmd;
        int i,flag=0;
        while(prefix[i]!=0){
        	if(prefix[i]!=s[i]){
        		flag++;
        		break;
			}
			i++;
		}
        if(flag==0){
            return p->cmd;
        }
        else{
            p=p->next;
        }
    }
    return NULL;
}
