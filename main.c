#include "header.h"
#include <ctype.h>

/* Check whether the string contains only digits.
   '-' is allowed only at the first position. */
int is_digit(char *str)
{
    int i = 0;

    if (str[0] == '\0')
        return 0;

    /* Allow negative number */
    if (str[0] == '-')
    {
        i = 1;

        /* Only '-' is not a valid number */
        if (str[1] == '\0')
            return 0;
    }

    for (; str[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)str[i]))
            return 0;
    }

    return 1;
}

int main(int argc, char *argv[])
{
    char *n1;
    char *n2;
    char op;

    Dlist *head1 = NULL;
    Dlist *tail1 = NULL;

    Dlist *head2 = NULL;
    Dlist *tail2 = NULL;

    Dlist *headR = NULL;
    Dlist *tailR = NULL;

    /* Check command line arguments */
    if (argc != 4)
    {
        printf("Usage: %s <number1> <operator> <number2>\n", argv[0]);
        printf("Example: %s 1234 + 567\n", argv[0]);
        return 0;
    }

    /* Get values from command line */
    n1 = argv[1];
    op = argv[2][0];
    n2 = argv[3];

    /* Validate numbers */
    if (!is_digit(n1) || !is_digit(n2))
    {
        printf("Invalid input: Enter numbers only\n");
        return 0;
    }

    /* Validate operator */
    if (op != '+' && op != '-' && op!='/' && op!='x')
    {
        printf("Invalid operator\n");
        return 0;
    }

    store_number(&head1, &tail1, n1);
    store_number(&head2, &tail2, n2);

    switch (op)
    {
        case '+':
            addition(tail1, tail2, &headR, &tailR);

            printf("Result = ");
            print_list(headR);
            break;

        case '-':
        {
            int negative = (compare(head1, head2) < 0);

            subtraction(head1, tail1,head2, tail2,&headR, &tailR);

            printf("Result = ");

            if (negative)
                printf("-");

            print_list(headR);
            break;
        }
        case 'x':
        {
        int sign = 1;

        if (n1[0] == '-')
            sign *= -1;

        if (n2[0] == '-')
            sign *= -1;

        multiplication(tail1, tail2,&headR, &tailR);

        printf("Result = ");

        if (sign < 0)
            printf("-");

        print_list(headR);
        break;
        }
        case '/':
        {
            
        int sign = 1;

        if (n1[0] == '-')
            sign *= -1;

        if (n2[0] == '-')
            sign *= -1;

        division(head1, head2,&headR, &tailR);

        printf("Result = ");

        if (sign < 0 && !(headR && headR->data == 0 && headR->next == NULL))
        printf("-");

        print_list(headR);
        break;
    }

        default:
            printf("Invalid operator\n");
            return 0;
    }
    

    free_list(&head1, &tail1);
    free_list(&head2, &tail2);
    free_list(&headR, &tailR);

    return 0;
}