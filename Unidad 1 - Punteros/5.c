#include<stdio.h>
#define TAM 10
void cargar(int *, int);
void mostrar(int *,int);
int* buscar(int *, int, int, int);

int main(){
    int v[TAM];
    int c,ini;
    int *p;
    cargar(v, TAM);
    mostrar(v, TAM);
    scanf("%d",&ini);
    scanf("%d",&c);
    p = buscar(v,c,ini,TAM);
    if(p != NULL)
    {
        printf("%d\n",p-v);
    }
    do{
        scanf("%d",&c);
        if(c>0)
        {
            p = buscar(v,c,0,TAM);
            if(p != NULL)
            {
                printf("%d\n",p-v);
            }
        }
    }while(c>0);
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


int* buscar(int *v, int busco, int ini, int tam)
{
    int *p = NULL;
    while(p == NULL && ini < tam)
    {
        if(*(v+ini) == busco)
        {
            p = v+ini;
        }
        ini++;
    }
    return p;
}