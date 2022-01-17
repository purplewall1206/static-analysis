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

int g;
extern int eg;
struct d dd;
struct d *pdd;
int lg[100];
struct d ldd[100];

int main()
{
    struct s x;
    x.a = 1;
    x.b = 2;
    x.c = 'c';
    x.h = &x.f;
    int *p = &(x.f.e);
    *p = 3;
    g = 10;
    eg = 11;
    head = 100;
    return 0;
}
