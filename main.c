#include "header.h"

int main(int argc, char *argv[])
{
    Dlist *head1 = NULL;
    Dlist *tail1 = NULL;

    Dlist *head2 = NULL;
    Dlist *tail2 = NULL;

    Dlist *headR = NULL;
    Dlist *tailR = NULL;

    /* Validate command line arguments */
    if (argc != 4)
    {
        printf("Usage: %s <number1> <operator> <number2>\n", argv[0]);
        printf("Example: %s 1234 + 567\n", argv[0]);
        return 1;
    }

    /* Store numbers in linked lists */
    store_number(&head1, &tail1, argv[1]);
    store_number(&head2, &tail2, argv[3]);

    /* Operator is the first character of argv[2] */
    char op = argv[2][0];

    /* Check whether operator is valid */
    if (argv[2][1] != '\0')
    {
        printf("Invalid operator\n");
        return 1;
    }

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

            subtraction(head1, tail1,
                        head2, tail2,
                        &headR, &tailR);

            printf("Result = ");

            if (negative)
                printf("-");

            print_list(headR);
            break;
        }

        default:
            printf("Invalid operator\n");
            return 1;
    }

    /* Free all allocated memory */
    free_list(&head1, &tail1);
    free_list(&head2, &tail2);
    free_list(&headR, &tailR);

    return 0;
}