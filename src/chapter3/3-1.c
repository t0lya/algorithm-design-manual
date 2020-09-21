#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool balanced_parentheses(char str[])
{
    int i;
    int count = 0;
    int length = strlen(str);

    for (i = 0; i < length; i++)
    {
        if (str[i] == '(')
        {
            count++;
        }
        else if (str[i] == ')')
        {
            count--;
        }

        if (count < 0)
        {
            printf("Imbalance at index %d\n", i);
            return false;
        }
    }

    return true;
}

int main()
{
    char test[] = "(sdaf(dsffs)sadf)gf))()";
    balanced_parentheses(test);
    char good[] = "dsf(df)dsf(df(gasfg))";
    printf("%d\n", balanced_parentheses(good));
    return 0;
}