#include "header.h"
#include <ctype.h>

/* Check whether the string contains only digits.
   '-' is allowed only at the first position. */
int is_digit(char *str)
{
    int i = 0;

    if (str[0] == '\0')
        return 0;

    if (str[0] == '-')
    {
        i = 1;

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

/* Return 1 if number is negative, otherwise 0 */
int is_negative(char *str)
{
    return (str[0] == '-');
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

    if (argc != 4)
    {
        printf("Usage: %s <number1> <operator> <number2>\n", argv[0]);
        printf("Example: %s 1234 + 567\n", argv[0]);
        return 0;
    }

    n1 = argv[1];
    op = argv[2][0];
    n2 = argv[3];

    if (!is_digit(n1) || !is_digit(n2))
    {
        printf("Invalid input: Enter numbers only\n");
        return 0;
    }

    if (op != '+' && op != '-' && op != '/' && op != 'x')
    {
        printf("Invalid operator\n");
        return 0;
    }

    /* Store magnitude only; signs are handled separately. */
    store_number(&head1, &tail1, (n1[0] == '-') ? n1 + 1 : n1);
    store_number(&head2, &tail2, (n2[0] == '-') ? n2 + 1 : n2);

    switch (op)
    {
        case '+':
        {
            int sign1 = is_negative(n1);
            int sign2 = is_negative(n2);
            int cmp = compare(head1, head2);

            printf("Result = ");

            if (sign1 == sign2)
            {
                /* Same signs: add magnitudes */
                addition(tail1, tail2, &headR, &tailR);

                if (sign1 && headR && !(headR->data == 0 && headR->next == NULL))
                    printf("-");
            }
            else
            {
                /* Different signs: subtract smaller magnitude from larger */
                if (cmp == 0)
                {
                    printf("0\n");
                    break;
                }

                if (cmp > 0)
                {
                    subtraction(head1, tail1, head2, tail2,
                                &headR, &tailR);

                    if (sign1)
                        printf("-");
                }
                else
                {
                    subtraction(head2, tail2, head1, tail1,
                                &headR, &tailR);

                    if (sign2)
                        printf("-");
                }
            }

            print_list(headR);
            break;
        }

        case '-':
        {
            int sign1 = is_negative(n1);
            int sign2 = is_negative(n2);
            int result_negative = 0;
            int cmp = compare(head1, head2);

            /*
               Mathematical rule:
               (+A) - (+B) = A-B
               (+A) - (-B) = A+B
               (-A) - (+B) = -(A+B)
               (-A) - (-B) = B-A
            */
            printf("Result = ");

            if (sign1 != sign2)
            {
                /* Different signs => magnitudes are added */
                addition(tail1, tail2, &headR, &tailR);

                result_negative = sign1;

                if (result_negative && headR &&
                    !(headR->data == 0 && headR->next == NULL))
                    printf("-");

                print_list(headR);
            }
            else
            {
                /* Same signs => subtract smaller magnitude from larger */
                if (cmp == 0)
                {
                    printf("0\n");
                }
                else if (cmp > 0)
                {
                    subtraction(head1, tail1, head2, tail2,
                                &headR, &tailR);

                    result_negative = sign1;

                    if (result_negative)
                        printf("-");

                    print_list(headR);
                }
                else
                {
                    subtraction(head2, tail2, head1, tail1,
                                &headR, &tailR);

                    /* If both were positive: A-B is negative.
                       If both were negative: -A-(-B) = B-A is positive. */
                    result_negative = !sign1;

                    if (result_negative)
                        printf("-");

                    print_list(headR);
                }
            }
            break;
        }

        case 'x':
        {
            int sign = is_negative(n1) ^ is_negative(n2);

            multiplication(tail1, tail2, &headR, &tailR);

            printf("Result = ");

            if (sign && headR && !(headR->data == 0 && headR->next == NULL))
                printf("-");

            print_list(headR);
            break;
        }

        case '/':
        {
            int sign = is_negative(n1) ^ is_negative(n2);

            division(head1, head2, &headR, &tailR);

            /*
               division() returns without creating a result
               when divisor is zero.
            */
            if (headR == NULL)
                break;

            printf("Result = ");

            if (sign && headR && !(headR->data == 0 && headR->next == NULL))
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