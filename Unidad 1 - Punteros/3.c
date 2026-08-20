#include <stdio.h>

void leer(int *, float *, char *);

int main()
{
    int a;
    float b;
    char c;
    leer(&a, &b, &c);
    printf("%d\n", a);
    printf("%f\n", b);
    printf("%c\n", c);
}

void leer(int *ptr1, float *ptr2, char *ptr3)
{
    scanf("%d", ptr1);
    scanf("%f", ptr2);
    getchar();
    scanf("%c", ptr3);
}