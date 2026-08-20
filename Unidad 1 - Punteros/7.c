#include<stdio.h>
#include<stdlib.h>

int main()
{
    int N,i, *v, *ptr;
    float suma = 0;
    printf("\nIngrese la cantidad de numeros: ");
    scanf("%d",&N);
    v = calloc(N, sizeof(int));
    if(v == NULL)
    {
        printf("\nError en la asignacion de memoria.");
        exit(1);
    }
    ptr = v;
    for(i=0;i<N;i++)
    {
        printf("\nIngrese el numero %d: ",i+1);
        scanf("%d",ptr);
        suma+=*ptr;
        ptr++;
    }
    ptr = v;
    for(i=0;i<N;i++)
    {
        printf("\n%d: %d",i+1,*ptr);
        ptr++;
    }
    printf("\nEl promedio es: %.2f",suma/N);
    free(v);
}