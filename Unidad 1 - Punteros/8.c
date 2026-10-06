#include <stdio.h>
#include <stdlib.h>

int IngrDatos();
void mostrarV(int *, int);
int main()
{
    int *v = NULL, N = 0, dni;
    dni = IngrDatos();
    while (dni != 0)
    {
        if (N % 5 == 0)
        {
            v = realloc(v, (N + 5) * sizeof(int));
            if(v==NULL)
            {
                printf("\nError en la asignacion de memoria!");
                free(v);
                exit(1);
            }
        }
        *(v+N) = dni;
        N++;
        dni = IngrDatos();
    };
    printf("\nLa cantidad de dnis existentes es: %d\n", N);
    mostrarV(v, N);
    free(v);
    return 0;
}
int IngrDatos()
{
    int dni;
    do
    {
        printf("\nIngrese un DNI valido: ");
        scanf("%d", &dni);
    } while (dni < 0);
    return dni;
}

void mostrarV(int *ptr, int N)
{
    int i;
    for (i = 0; i < N; i++)
    {
        printf("%d ", *(ptr+i));
    }
}