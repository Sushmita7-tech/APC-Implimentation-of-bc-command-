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

    while (*headR &&(*headR)->data == 0 &&(*headR)->next)
    {
        Dlist *temp = *headR;

        *headR = (*headR)->next;
        (*headR)->prev = NULL;

        free(temp);
    }
}

void multiplication(Dlist *tail1, Dlist *tail2,Dlist **headR, Dlist **tailR)
{
    int arr1[1000];
    int arr2[1000];
    int result[2000] = {0};

    int len1 = 0;
    int len2 = 0;

    while (tail1)
    {
        arr1[len1++] = tail1->data;
        tail1 = tail1->prev;
    }

    while (tail2)
    {
        arr2[len2++] = tail2->data;
        tail2 = tail2->prev;
    }

    for (int i = 0; i < len1; i++)
    {
        int carry = 0;

        for (int j = 0; j < len2; j++)
        {
            int temp = result[i + j] +
                       (arr1[i] * arr2[j]) +
                       carry;

            result[i + j] = temp % 10;
            carry = temp / 10;
        }

        result[i + len2] += carry;
    }

    int size = len1 + len2;

    while (size > 1 && result[size - 1] == 0)
    {
        size--;
    }

    /* Store result in DLL */
    for (int i = size - 1; i >= 0; i--)
    {
        insert_last(headR, tailR, result[i]);
    }
}
/* DIVISION */
void division(Dlist *head1, Dlist *head2,Dlist **headR, Dlist **tailR)
{
    long long num1 = 0;
    long long num2 = 0;

    
    while (head1)
    {
        num1 = num1 * 10 + head1->data;
        head1 = head1->next;
    }

    while (head2)
    {
        num2 = num2 * 10 + head2->data;
        head2 = head2->next;
    }

    if (num2 == 0)
    {
        printf("Division by zero\n");
        return;
    }

    long long result = num1 / num2;

    char str[100];

    sprintf(str, "%lld", result);

    store_number(headR, tailR, str);
}