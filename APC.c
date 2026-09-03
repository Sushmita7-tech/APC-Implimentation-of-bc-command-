#include "header.h"

void insert_first(Dlist **head,Dlist **tail,int data){
    Dlist *new;
    new=malloc(sizeof(Dlist));
    
    if(new==NULL){
        return ;
    }
    
    new->data=data;
    new->prev=NULL;
    new->next=*head;
    if(*head==NULL){
        
        *head=*tail=new;
        return ;
    }
    
    (*head)->prev=new;
    *head=new;
    
}

void store_number(Dlist **head,Dlist **tail,char *str)