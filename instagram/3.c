//@morillokovac
#include<stdio.h>

void Ordenar(int[], int);

int main()
{















}

void Ordenar(int v[], int tam)
{
    int i, j, aux;
    for(i=0;i<tam-1;i++)
    {
        for(j=0;j<tam-i-1; j++)
        {
            if(v[i] > v[j]) //Ordena de forma ascendente. 
            //Si queremos que los mayores vayan antes
            //Hay que poner v[i] < v[j]. Recordemos que i son los elementos
            //que van antes
            {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
}