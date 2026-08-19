#include <stdio.h>

void asignar(int*);

int main()
{
    int n;
    int *ptr = &n;
    asignar(ptr);
    printf("%d\n",&n);
    printf("%d\n",&ptr);
    printf("%d\n",n);
    printf("%d\n",*ptr);
    printf("%d\n",ptr);
}

void asignar(int *n)
{
    *n = 10;
}
