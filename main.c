#include "header.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char argv[]){

    if(argc!=4){
        printf("currect way for input is :%s <num1> <operator> <num2>\n",argv[0]);

        return FAILURE;
    }


    char *n1;
    char *n2;
    char op;
    

    Dlist *head1=NULL;
    Dlist *tail1=NULL;

    Dlist *head2=NULL;
    Dlist *tail2=NULL;

    Dlist *reshead=NULL;
    Dlist *restail=NULL;

    n1=argv[1];
    n2=argv[2];
    op=argv[2][0];

    store_number(&head1,&tail1,n1);
    store_number(&head2,&tail2,n2);

    switch(op){
        case '+':addition(tail1,tail2,&reshead,&restail);
                    printf("res=");
                    print_list(reshead);
                    break;
    }

    
}