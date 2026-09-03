#ifndef APC_H
#define APC_H

#define FAILURE 1;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node{

    int data;
    struct node *prev;
    struct node *next;
}Dlist;

void insert_first(Dlist **head,Dlist **tail,int data);
void print_list(Dlist *head);
void store_number(Dlist **head,Dlist **tail,char *str);
void addition(Dlist *tail1,Dlist *tail2,Dlist *reshead,Dlist *restail);
int validate(char *str);


#endif