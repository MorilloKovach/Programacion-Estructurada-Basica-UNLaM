/*
Crear una función que defina en memoria dinámica un vector de 10 elementos cargados de forma aleatoria
con números de 2 cifras, la función debe mostrar los datos generados en forma ordenada de mayor a menor.
Desde el main invocar la función 5 veces para visualizar 5 vectores distintos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 10

void crearVector(int);
void ordenarVector(int *, int);
void mostrarVector(int *, int);
int posMinimo(int *, int, int);
int main()
{
    int i;
    srand(time(NULL));
    for (i = 0; i < 5; i++)
    {
        crearVector(TAM);
    }
}
void crearVector(int tam)
{
    int *v = calloc(tam, sizeof(int)), *ptr;
    if (v == NULL)
    {
        printf("\nError en la asignacion de memoria.");
        exit(1);
    }
    int i;
    ptr = v;
    for (i = 0; i < tam; i++)
    {
        *ptr = rand() % 90 + 10;
        ptr++;
    }
    ordenarVector(v, TAM);
    mostrarVector(v, TAM);
    free(v);
}

int posMinimo(int *v, int ini, int tam)
{
    int i, posMin = ini;
    for (i = ini + 1; i < tam; i++)
    {
        if (*(v + i) > *(v + posMin))
        {
            posMin = i;
        }
    }
    return posMin;
}

void ordenarVector(int *v, int tam)
{
    int i, j, aux;
    for (i = 0; i < tam; i++)
    {
        j = posMinimo(v, i, tam);
        if (i != j)
        {
            aux = *(v+i);
            *(v+i) = *(v + j);
            *(v + j) = aux;
        }
    }
}

void mostrarVector(int *v, int tam)
{
    int i, *ptr;
    ptr = v;
    for (i = 0; i < tam; i++)
    {
        printf("%d ", *ptr);
        ptr++;
    }
    printf("\n");
}
