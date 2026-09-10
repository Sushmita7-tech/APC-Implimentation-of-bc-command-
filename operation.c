#include "header.h"

/* ADDITION - works on magnitudes only */
void addition(Dlist *tail1, Dlist *tail2,
              Dlist **headR, Dlist **tailR)
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

        insert_first(headR, tailR, sum % 10);
    }
}


/* SUBTRACTION - subtracts smaller magnitude from larger magnitude */
void subtraction(Dlist *head1, Dlist *tail1,
                 Dlist *head2, Dlist *tail2,
                 Dlist **headR, Dlist **tailR)
{
    int borrow = 0;

    /* Always calculate larger magnitude - smaller magnitude */
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

        insert_first(headR, tailR, diff);

        tail1 = tail1->prev;
    }

    /* Remove leading zeros */
    while (*headR && (*headR)->data == 0 && (*headR)->next)
    {
        Dlist *temp = *headR;

        *headR = (*headR)->next;
        (*headR)->prev = NULL;

        free(temp);
    }
}


void multiplication(Dlist *tail1, Dlist *tail2,
                     Dlist **headR, Dlist **tailR)
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
        size--;

    for (int i = size - 1; i >= 0; i--)
        insert_last(headR, tailR, result[i]);
}


/* DIVISION - supports numbers of any length */
void division(Dlist *head1, Dlist *head2,
              Dlist **headR, Dlist **tailR)
{
    Dlist *p1 = head1;
    Dlist *remainderHead = NULL;
    Dlist *remainderTail = NULL;

    /* Find the tail of divisor. subtraction() needs both head and tail. */
    Dlist *tail2 = head2;
    while (tail2 && tail2->next)
        tail2 = tail2->next;

    /* Division by zero check */
    if (head2 == NULL)
    {
        printf("Division by zero\n");
        return;
    }

    /* Check whether divisor is actually 0 */
    Dlist *temp = head2;
    while (temp && temp->data == 0)
        temp = temp->next;

    if (temp == NULL)
    {
        printf("Division by zero\n");
        return;
    }

    /*
     * Long division:
     * Bring down one digit at a time.
     * For every digit, find the quotient digit (0 to 9)
     * by repeatedly subtracting the divisor from remainder.
     */
    while (p1)
    {
        /* Bring down the next digit */
        insert_last(&remainderHead, &remainderTail, p1->data);

        /* Remove leading zeros from remainder */
        while (remainderHead &&
               remainderHead->data == 0 &&
               remainderHead->next)
        {
            Dlist *del = remainderHead;
            remainderHead = remainderHead->next;
            remainderHead->prev = NULL;
            free(del);
        }

        int quotientDigit = 0;

        /*
         * A quotient digit can only be 0..9.
         * Subtract divisor while remainder >= divisor.
         */
        while (remainderHead &&
               compare(remainderHead, head2) >= 0 &&
               quotientDigit < 10)
        {
            Dlist *newRemHead = NULL;
            Dlist *newRemTail = NULL;

            subtraction(remainderHead, remainderTail,
                        head2, tail2,
                        &newRemHead, &newRemTail);

            /* Free old remainder */
            while (remainderHead)
            {
                Dlist *del = remainderHead;
                remainderHead = remainderHead->next;
                free(del);
            }

            remainderHead = newRemHead;
            remainderTail = newRemTail;

            quotientDigit++;
        }

        insert_last(headR, tailR, quotientDigit);

        p1 = p1->next;
    }

    /*
     * Remove leading zeros from quotient.
     * Keep one zero if the complete quotient is zero.
     */
    while (*headR && (*headR)->data == 0 && (*headR)->next)
    {
        Dlist *del = *headR;
        *headR = (*headR)->next;
        (*headR)->prev = NULL;
        free(del);
    }

    /* Free remainder */
    while (remainderHead)
    {
        Dlist *del = remainderHead;
        remainderHead = remainderHead->next;
        free(del);
    }

    /*
     * tailR may have become invalid only if the result was empty.
     * Normally the result always contains at least one digit.
     */
    if (*headR)
    {
        *tailR = *headR;
        while ((*tailR)->next)
            *tailR = (*tailR)->next;
    }
}