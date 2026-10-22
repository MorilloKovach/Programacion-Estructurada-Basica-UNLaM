/*
 Realizar un programa que permita buscar un contacto en el archivo de agenda generado en punto anterior,
por apellido o nombre y mostrar el / los datos coincidentes si los hay. 
*/

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct
{
    char apellido[51];
    char nombre[51];
    char correo[101];
    char telefono[11];
} Datos;

void LeerTexto(char[], int);

void tocarSector(Datos *, char *, int);

int main()
{
    Datos d;
    char nom[51];
    FILE *fp = fopen("agenda.txt", "r");
    char *parte;
    char linea[300];
    int part = 0;
    printf("\nIngrese el nombre o el apellido que desea buscar: ");
    LeerTexto(nom, 51);
    while(fgets(linea, 300, fp))
    {
        parte = strtok(linea, ";");
        part = 1;
        while(parte != NULL)
        {
            tocarSector(&d, parte, part);
            parte = strtok(NULL, ";");
            part++;
        }
        if(strcmp(d.nombre, nom) == 0 || strcmp(d.apellido, nom) == 0)
        {
            printf("\n%s %s %s %s\n", d.nombre, d.apellido, d.correo, d.telefono);
        }
    }
    fclose(fp);

    return 0;
}
void tocarSector(Datos *d, char *s, int p)
{
    switch(p)
    {
        case 1:
            strcpy(d->nombre, s);
            break;
        case 2:
            strcpy(d->apellido, s);
            break;
        case 3:
            strcpy(d->correo, s);
            break;
        default:
            strcpy(d->telefono, s);
    }
}
void LeerTexto(char str[], int tam)
{
    int i = 0;
    fgets(str, tam, stdin);
    while (i < tam && str[i] != '\0')
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
        }
        else
        {
            i++;
        }
    }
}