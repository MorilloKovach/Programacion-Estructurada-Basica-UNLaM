#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 5
#define SZ 30

typedef struct
{
    int legajo;
    char sexo;
    char nombre[SZ];
    float promedio;
} Alumno;

char *Leer(int);
void cargarDatos(Alumno *, int, int);
void mostrarAlumnos(Alumno *, int);

int main()
{
    Alumno *v;
    v = calloc(TAM, sizeof(Alumno));
    if (v != NULL)
    {
        cargarDatos(v, TAM, SZ);
        mostrarAlumnos(v, TAM);
    }
    else
    {
        printf("\nERROR. NO SE PUDO ASIGNAR TAMAÑO AL VECTOR");
    }
    free(v);
    return 0;
}

void mostrarAlumnos(Alumno *v, int tam)
{
    int i, idx = 0;
    float prom = 0.0;
    for (i = 0; i < tam; i++)
    {
        if ((v + i)->promedio > prom)
        {
            idx = i;
            prom = (v + i)->promedio;
        }
        printf("\n%s\n", (v + i)->nombre);
    }
    printf("\nEl alumno con mejor promedio fue: %s", (v + idx)->nombre);
}
void cargarDatos(Alumno *v, int tam, int tamStr)
{
    int i;
    char *aux;
    for (i = 0; i < tam; i++)
    {
        printf("\nIngrese el legajo: ");
        scanf("%d", &(v + i)->legajo);
        printf("\nIngrese el sexo: ");
        getchar();
        scanf("%c", &(v + i)->sexo);
        while ((v + i)->sexo != 'F' && (v + i)->sexo != 'M')
        {
            printf("\nIngrese un sexo valido: ");
            getchar();
            scanf("%c", &(v + i)->sexo);
        }
        printf("\nIngrese el nombre: ");
        getchar();
        aux = Leer(tamStr);
        strcpy((v + i)->nombre, aux);
        printf("\nIngrese el promedio: ");
        scanf("%f", &(v + i)->promedio);
        while ((v + i)->promedio < 1 || (v + i)->promedio > 10)
        {
            printf("\nIngrese un promedio valido: ");
            scanf("%f", &(v + i)->promedio);
        }
        free(aux);
    }
}
char *Leer(int tam)
{
    int i = 0;
    char *s;
    s = calloc(tam, sizeof(char));
    fgets(s, tam, stdin);
    while (i < tam && *(s + i) != '\0')
    {
        if (*(s + i) == '\n')
        {
            *(s + i) = '\0';
        }
        else
        {
            i++;
        }
    }
    return s;
}

/*
123
F
TOMY
9

321
F
BUCHU
8

235
M
SANTIAGO
10

543
M
TIZIANO
9.75

934
M
FABRIZIO
8
*/