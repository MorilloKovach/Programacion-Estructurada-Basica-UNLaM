#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<peb.h>
#define TAM 10

int* encontrar(int*, int);

int main()
{
    srand(time(NULL));
    int v[TAM];
    int *p = v;
    int i;
    for(i=0;i<TAM;i++)
    {
        *p = rand()%1000;
        p++;
    }
    p = encontrar(v,TAM);
    printf("%d ",*p);
    printf("%d",p-v);
}

int* encontrar(int *v, int tam)
{
    int max = 0,i;
    int *ptr = v;
    int *pr = NULL;
    for(i=0;i<tam;i++)
    {
        if(*ptr > max)
        {
            max = *ptr;
            pr = ptr;
        }
        ptr++;
    }
    return pr;
}