#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
} Dlist;

/* DLL Functions */
void insert_last(Dlist **head, Dlist **tail, int data);
void insert_first(Dlist **head, Dlist **tail, int data);
void print_list(Dlist *head);
void free_list(Dlist **head, Dlist **tail);

/* Utility Functions */
void store_number(Dlist **head, Dlist **tail, char *str);
int compare(Dlist *head1, Dlist *head2);

/* Arithmetic Functions */
void addition(Dlist *tail1, Dlist *tail2,Dlist **headR, Dlist **tailR);

void subtraction(Dlist *head1, Dlist *tail1,Dlist *head2, Dlist *tail2,Dlist **headR, Dlist **tailR);

void multiplication(Dlist *tail1, Dlist *tail2,Dlist **headR, Dlist **tailR);

void division(Dlist *head1, Dlist *head2,Dlist **headR, Dlist **tailR);

#endif