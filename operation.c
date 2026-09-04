#include "header.h"

/* ADDITION */
void addition(Dlist *tail1, Dlist *tail2,Dlist **headR, Dlist **tailR)
{
    int carry = 0;

    while (tail1 || tail2 || carry)
    {
        int sum = carry;

        if (tail1)
        {
            sum += tail1->data;
            tail1 = tail1->prev;
        }

        if (tail2)
        {
            sum += tail2->data;
            tail2 = tail2->prev;
        }

        carry = sum / 10;

        Dlist *new = malloc(sizeof(Dlist));
        new->data = sum % 10;
        new->prev = NULL;
        new->next = *headR;

        if (*headR)
            (*headR)->prev = new;
        else
            *tailR = new;

        *headR = new;
    }
}


/* SUBTRACTION */
void subtraction(Dlist *head1, Dlist *tail1,Dlist *head2, Dlist *tail2,Dlist **headR, Dlist **tailR)
{
    int borrow = 0;

    if (compare(head1, head2) < 0)
    {
        Dlist *temp;

        temp = head1;
        head1 = head2;
        head2 = temp;

        temp = tail1;
        tail1 = tail2;
        tail2 = temp;
    }

    while (tail1)
    {
        int diff = tail1->data - borrow;

        if (tail2)
        {
            diff -= tail2->data;
            tail2 = tail2->prev;
        }

        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        Dlist *new = malloc(sizeof(Dlist));

        new->data = diff;
        new->prev = NULL;
        new->next = *headR;

        if (*headR)
            (*headR)->prev = new;
        else
            *tailR = new;

        *headR = new;

        tail1 = tail1->prev;
    }

    while (*headR &&
           (*headR)->data == 0 &&
           (*headR)->next)
    {
        Dlist *temp = *headR;

        *headR = (*headR)->next;
        (*headR)->prev = NULL;

        free(temp);
    }
}