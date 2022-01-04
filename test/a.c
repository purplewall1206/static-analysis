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
    int *p = &(x.f.e);
    *p = 3;
    printf("%d %u %c %d\n", x.a, x.b, x.c, x.f.e);
    return 0;
}
