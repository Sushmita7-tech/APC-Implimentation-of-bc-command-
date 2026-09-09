#include "header.h"

void insert_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));

    if (new == NULL)
        return;

    new->data = data;
    new->next = NULL;
    new->prev = NULL;

    if (*head == NULL)
    {
        *head = *tail = new;
        return;
    }

    (*tail)->next = new;
    new->prev = *tail;
    *tail = new;
}

void insert_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));

    if (new == NULL)
        return;

    new->data = data;
    new->prev = NULL;
    new->next = *head;

    if (*head == NULL)
    {
        *head = *tail = new;
        return;
    }

    (*head)->prev = new;
    *head = new;
}

void store_number(Dlist **head, Dlist **tail, char *str)
{
    int i = 0;

    if (str[0] == '-')
        i = 1;

    while (str[i] != '\0')
    {
        insert_last(head, tail, str[i] - '0');
        i++;
    }
}
void print_list(Dlist *head)
{
    if (head == NULL)
    {
        printf("0\n");
        return;
    }

    while (head)
    {
        printf("%d", head->data);
        head = head->next;
    }

    printf("\n");
}

void free_list(Dlist **head, Dlist **tail)
{
    Dlist *temp = *head;

    while (temp)
    {
        Dlist *next = temp->next;
        free(temp);
        temp = next;
    }

    *head = NULL;
    *tail = NULL;
}

int compare(Dlist *head1, Dlist *head2)
{
    // Remove leading zeros from first number
    while (head1 && head1->data == 0)
        head1 = head1->next;

    // Remove leading zeros from second number
    while (head2 && head2->data == 0)
        head2 = head2->next;

    // Both numbers are zero
    if (head1 == NULL && head2 == NULL)
        return 0;

    // Find lengths after removing leading zeros
    int len1 = 0;
    int len2 = 0;

    Dlist *temp1 = head1;
    Dlist *temp2 = head2;

    while (temp1)
    {
        len1++;
        temp1 = temp1->next;
    }

    while (temp2)
    {
        len2++;
        temp2 = temp2->next;
    }

    // Compare number of digits
    if (len1 > len2)
        return 1;

    if (len1 < len2)
        return -1;

    // Same number of digits → compare digit by digit
    while (head1 && head2)
    {
        if (head1->data > head2->data)
            return 1;

        if (head1->data < head2->data)
            return -1;

        head1 = head1->next;
        head2 = head2->next;
    }

    return 0;
}