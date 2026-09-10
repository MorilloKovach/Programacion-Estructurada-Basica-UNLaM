/*
6. La fórmula 1 está compuesta por 20 pilotos y en el año se corrieron 23 carreras.
a) Se desea ingresar la información de cada piloto (nombre, escudería) y la posición en la que llegó dicho
piloto en cada una de las 23 carreras (1 a 20).
b) Luego se debe poder elegir el número de carrera del año y mostrar el listado de los 10 primeros puestos
de dicha carrera. Repetir el proceso con distintos números de carreras hasta ingresar un 0 como número
de carrera.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CARRERAS 5
#define PILOTOS 20
typedef struct
{
    char *nom, *esc;
    int *pos;
} Piloto;

int existePos(Piloto *, int, int, int);
void VisualizarCarrera(Piloto *, int);
void IngresoDatos(Piloto *, int, int);
void AsignarPosiciones(Piloto *, int, int);
void LeerCarreras(Piloto *, int);
int ValidacionCarrera(int);
void vaciarTodo(Piloto *, int);
void Leer(char*, int);
int main()
{
    int estado = 0;
    Piloto *p;
    p = calloc(PILOTOS, sizeof(Piloto));
    if (p != NULL)
    {
        IngresoDatos(p, PILOTOS, CARRERAS);
        AsignarPosiciones(p, CARRERAS, PILOTOS);
        LeerCarreras(p, CARRERAS);
        vaciarTodo(p, PILOTOS);
    }
    else
    {
        printf("\nError en la asignacion.");
        estado = 1;
    }
    free(p);
    return estado;
}

void Leer(char *ap, int tam)
{
    int i = 0;
    fgets(ap, tam, stdin);

    while (i < tam && ap[i] != '\0')
    {
        if (ap[i] == '\n')
        {
            ap[i] = '\0';
        }
        else
        {
            i++;
        }
    }
}

void vaciarTodo(Piloto *p, int pilotos)
{
    int i;
    for (i = 0; i < pilotos; i++)
    {
        free((p + i)->esc);
        free((p + i)->nom);
        free((p + i)->pos);
    }
}

int ValidacionCarrera(int lsup)
{
    int carrera;
    printf("\nIngrese una carrera: ");
    scanf("%d", &carrera);
    while (carrera < 0 || carrera > lsup)
    {
        printf("\nIngrese una carrera valida: ");
        scanf("%d", &carrera);
    }
    return carrera;
}

void LeerCarreras(Piloto *p, int carreras)
{
    int carrera = ValidacionCarrera(carreras);
    while (carrera != 0)
    {
        VisualizarCarrera(p, carrera - 1);
        carrera = ValidacionCarrera(carreras);
    }
}
void AsignarPosiciones(Piloto *p, int carreras, int pilotos)
{
    int i, j, pivotarTop;
    for (i = 0; i < pilotos; i++)
    {
        printf("\n\n PILOTO %s\n\n", ((p + i)->nom));
        for (j = 0; j < carreras; j++)
        {
            printf("\nIngrese la pos en la carrera %d del piloto: ", j + 1);
            scanf("%d", &pivotarTop);
            while (existePos(p, pivotarTop, i, j) || pivotarTop > pilotos || pivotarTop < 1)
            {
                printf("\nEsa pos ya esta ocupada o no esta en el intervalo, seleccione otra: ");
                scanf("%d", &pivotarTop);
            }
            *((p + i)->pos + j) = pivotarTop;
        }
    }
}
void IngresoDatos(Piloto *p, int pilotos, int carreras)
{
    int i;
    for (i = 0; i < pilotos; i++)
    {
        (p + i)->nom = calloc(50, sizeof(char));
        (p + i)->esc = calloc(50, sizeof(char));
        (p + i)->pos = calloc(carreras, sizeof(int));
        printf("\nIngrese el nombre del piloto: ");
        Leer((p+i)->nom,50);
        printf("\nIngrese la escuderia: ");
        Leer((p+i)->esc,50);
    }
}
void VisualizarCarrera(Piloto *p, int carreras)
{
    int i;
    int pos;
    for (pos = 1; pos <= 10; pos++)
    {
        for (i = 0; i < PILOTOS; i++)
        {
            if (*((p + i)->pos + carreras) == pos)
            {
                printf("\nLa pos en la carrera del piloto %s fue: %d\n", (p + i)->nom, *((p + i)->pos + carreras));
            }
        }
    }
}

int existePos(Piloto *p, int top, int piloto, int carrera)
{
    int flag = 0, i = 0;
    while (i < piloto && flag == 0)
    {
        if (*((p + i)->pos + carrera) == top)
        {
            flag = 1;
        }
        else
        {
            i++;
        }
    }
    return flag;
}