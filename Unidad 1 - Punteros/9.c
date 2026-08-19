#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define TAM 10


void crearVector();
void ordenarVector(int*);
void mostrarVector(int*);

int main()
{
    int i;
    srand(time(NULL));
    for(i=0;i<5;i++)
    {
        crearVector();
    }
}
void crearVector()
{
    int *v = calloc(TAM, sizeof(int)), *ptr;
    int i;
    ptr = v;
    for(i=0;i<TAM;i++)
    {
        *ptr = rand()%100;
        ptr++;
    }
    ordenarVector(v);
    mostrarVector(v);
    free(v);
}

void ordenarVector(int *v)
{
    int *ptr1 = v, *ptr2;
    int i,j,aux,*ptr3;
    for(i=0;i<TAM;i++)
    {
        ptr2 = v+i+1;
        ptr3 = ptr1;
        for(j=i+1;j<TAM;j++)
        {
            if(*ptr3 < *ptr2)
            {
                ptr3 = ptr2;
            }
            ptr2++;
        }
        if(ptr3 != ptr1)
        {
            aux = *ptr3;
            *ptr3 = *ptr1;
            *ptr1 = aux;
        }
        ptr1++;
    }
}

void mostrarVector(int *v)
{
    int i, *ptr;
    ptr = v;
    for(i=0;i<TAM;i++)
    {
        printf("%d ",*ptr);
        ptr++;
    }
    printf("\n");
}
