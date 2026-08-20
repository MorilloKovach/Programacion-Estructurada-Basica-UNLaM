#include <stdio.h>
#include <stdlib.h>

int IngrDatos();
void mostrarV(int *, int);
int main()
{
    int *v = NULL, *ptr, *tmp, N = 0, dni;
    ptr = v;
    dni = IngrDatos();
    while (dni != 0)
    {
        if (N % 5 == 0)
        {
            tmp = (int *)realloc(v, (N + 5) * sizeof(int));
            if(tmp==NULL)
            {
                printf("\nError en la asignacion de memoria!");
                free(v);
                exit(1);
            }
            v = tmp;
            ptr = v + N;
        }
        *ptr = dni;
        ptr++;
        N++;
        dni = IngrDatos();
    };
    printf("\nLa cantidad de dnis existentes es: %d\n", N);
    ptr = v;
    mostrarV(ptr, N);
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
        printf("%d ", *ptr);
        ptr++;
    }
}