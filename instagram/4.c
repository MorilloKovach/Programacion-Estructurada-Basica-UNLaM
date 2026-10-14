//@morillokovac
#include<stdio.h>

void CargaSegura(int[], int);
int LeerYValidarEntero(int, int, int);

int main()
{












}

int LeerYValidarEntero(int linf, int lsup, int corte)
{
    int num;
    do
    {
        printf("\nIngrese un valor (entre %d y %d): ",linf,lsup);
        scanf("%d",&num);
    }while((num < linf || num > lsup) && num != corte);
    return num;
}

void CargaSegura(int v[], int tam)
{
    //Ya se sabe que van a exitir tam elementos cargados de antemano.
    int i, val;
    for(i=0;i<tam;i++)
    {
        val = LeerYValidarEntero(1000, 9999, 0);
        v[i] = val;
    }
}