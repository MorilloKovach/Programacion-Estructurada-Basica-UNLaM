#include<stdio.h>

int sumar(int*,int*);

int main()
{
    int a,b;
    int *p1=&a, *p2=&b;
    scanf("%d%d",&a,&b);
    printf("%d\n",sumar(p1,p2));
}

int sumar(int *a, int *b)
{
    return *a + *b;
}