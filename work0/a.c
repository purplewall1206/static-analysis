// #include <stdio.h>
#include "header.h"


struct s
{
    int a;
    unsigned int b;
    char c;
    struct d f;
    struct d *h;
};

int main()
{
    struct s x;
    x.a = 1;
    x.b = 2;
    x.c = 'c';
    x.h = &x.f;
    int *p = &(x.f.e);
    *p = 3;
    return 0;
}
