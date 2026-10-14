//@morillokovac
#include<stdio.h>

int CargaParcial(int[], int);
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

int CargaParcial(int v[], int cantMax)
{
    int i = 0, val=0;
    val = LeerYValidarEntero(1000, 9999, 0);
    while(i<cantMax && val != 0)
    {
        v[i] = val;
        printf("\nIngrese el valor: "); //Codigo o lo que sea
        val = LeerYValidarEntero(1000, 9999, 0);
    } 
    return i;
}