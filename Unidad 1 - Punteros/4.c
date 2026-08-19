#include<stdio.h>
#define TAM 10
void cargar(int *, int);
void mostrar(int *,int);

int main(){
    int v[TAM];
    cargar(v, TAM);
    mostrar(v, TAM);
}

void cargar(int *v,int tam)
{
    int i = 0;
    for(i;i<tam;i++)
    {
        scanf("%d",(v+i));
    }
}

void mostrar(int *v, int tam)
{
    int i=0;
    for(i;i<tam;i++)
    {
        printf("%d ",*(v+i));
    }
}