#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
    char nom[31];
    int dni;
} alumno;
#define MAX_A 50

void cargarAlumnos(alumno *, int);
void mostrarAlumnos(alumno *, int);

int main()
{
    alumno *a;
    int tam=MAX_A;
    a = calloc(MAX_A, sizeof(alumno));
    if (a != NULL)
    {
        cargarAlumnos(a, tam);
        mostrarAlumnos(a, tam);
    }
    else
    {
        printf("\nError en la asignacion de memoria");
        exit(1);
    }
    return 0;
}

void cargarAlumnos(alumno *a, int tam)
{
    int i=0, dni;
    char nom[31];
    for(i=0;i<tam;i++)
    {
        printf("\nIngrese el dni del alumno %d: ", i+1);
        scanf("%d",&dni);
        (a+i)->dni = dni;
        printf("\nIngrese el nombre del alumno %d: ", i+1);
        scanf("%s",nom);
        strcpy((a+i)->nom, nom);
    }
}

void mostrarAlumnos(alumno *a, int tam)
{
    int i;
    printf("\nNOMBRE\t DNI");
    for(i=0;i<tam;i++)
    {
        printf("\n%d\t %s", (a+i)->dni, (a+i)->nom);
    }
}