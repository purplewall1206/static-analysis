#include <stdio.h>
#include "header.h"


struct s
{
    int a;
    unsigned int b;
    char c;
    struct d f;
};

int main()
{
    struct s x;
    x.a = 1;
    x.b = 2;
    x.c = 'c';
    printf("%d %u %c\n", x.a, x.b, x.c);
    return 0;
}
