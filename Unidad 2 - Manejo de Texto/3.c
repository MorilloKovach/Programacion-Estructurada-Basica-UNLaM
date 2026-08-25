#include <stdio.h>
#include <string.h>
int cargaAlumnos(char[][20], int *, int);
int *Buscar(char[][20], int *, char *, int);
void leer(char[], int);
void ordenar(char[][20], int[], int);
void mostrar(char[][20], int[], int);
int main()
{
    int cantTot, DNISAlumnos[50], *pos;
    char AlumnosNombres[50][20], nombre[20];
    cantTot = cargaAlumnos(AlumnosNombres, DNISAlumnos, 50);
    printf("\nIngrese un nombre a buscar: ");
    scanf("%s", nombre);
    while (strcmp(nombre, "NOBUSCARMAS") != 0)
    {
        pos = Buscar(AlumnosNombres, DNISAlumnos, nombre, cantTot);
        if (pos != NULL)
            printf("%d\n", *pos);
        else
            printf("El alumno no esta en el curso.\n");
        printf("\nIngrese otro nombre: ");
        scanf("%s", nombre);
    }
    ordenar(AlumnosNombres, DNISAlumnos, cantTot);
    mostrar(AlumnosNombres, DNISAlumnos, cantTot);
    return 0;
}

int *Buscar(char AlumnosNombres[][20], int *DNISAlumnos, char *nombre, int tam)
{
    int i = 0, *pos = NULL;
    while (i < tam && pos == NULL)
    {
        if (strcmp(*(AlumnosNombres + i), nombre) == 0)
        {
            pos = (DNISAlumnos + i);
        }
        i++;
    }
    return pos;
}

int cargaAlumnos(char AlumnosNombres[][20], int *DNISAlumnos, int tam)
{
    int i = 0;
    char nombre[20];
    printf("\nIngrese un nombre: ");
    scanf("%s", nombre);
    while (i < tam && strcmp(nombre, "FIN") != 0)
    {
        strcpy(AlumnosNombres[i], nombre);
        printf("\nIngrese un DNI: ");
        scanf("%d", &DNISAlumnos[i]);
        while (DNISAlumnos[i] < 0)
        {
            printf("\nIngrese un DNI valido: ");
            scanf("%d", &DNISAlumnos[i]);
        }
        printf("\nIngrese un nombre: ");
        scanf("%s", nombre);
        i++;
    }
    return i;
}

void leer(char nombre[], int largo)
{
    int i;
    getchar();
    fgets(nombre, largo, stdin);
    i = 0;
    while (nombre[i] != '\0')
    {
        if (nombre[i] == '\n')
        {
            nombre[i] = '\0';
        }
        else
            i++;
    }
}

void ordenar(char nombres[][20], int dnis[], int tam)
{
    int i, j, aux2;
    char aux[20];
    for (i = 0; i < tam - 1; i++)
    {
        for (j = 0; j < tam - 1 - i; j++)
        {
            if (strcmp(nombres[j], nombres[j + 1]) > 0)
            {
                strcpy(aux, nombres[j]);
                strcpy(nombres[j], nombres[j + 1]);
                strcpy(nombres[j + 1], aux);

                aux2 = dnis[j];
                dnis[j] = dnis[j + 1];
                dnis[j + 1] = aux2;
            }
        }
    }
}

void mostrar(char nombres[][20], int dnis[], int tam)
{
    int i;
    for (i = 0; i < tam; i++)
    {
        printf("%s \t %d\n", nombres[i], dnis[i]);
    }
}