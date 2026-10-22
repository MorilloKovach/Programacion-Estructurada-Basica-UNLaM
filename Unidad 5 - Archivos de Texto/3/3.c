#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LeerTexto(char[], int);

typedef struct
{
    char apellido[51];
    char nombre[51];
    char correo[101];
    char telefono[11];
} Datos;

int main()
{
    FILE *fp = fopen("agenda.txt", "w");
    Datos p;
    if (fp == NULL)
    {
        printf("\nNo se pudo crear el archivo");
        system("pause");
        exit(1);
    }
    printf("\nIngrese el nombre: ");
    LeerTexto(p.nombre, 51);
    printf("\nIngrese el apellido: ");
    LeerTexto(p.apellido, 51);
    while (strcmp(p.nombre, "FINALIZAR") != 0 || strcmp(p.apellido, "FINALIZAR") != 0)
    {
        printf("\nIngrese el correo: ");
        LeerTexto(p.correo, 101);
        printf("\nIngrese el telefono: ");
        LeerTexto(p.telefono, 11);
        fprintf(fp, "%s;%s;%s;%s\n", p.nombre, p.apellido, p.correo, p.telefono);
        printf("\nIngrese otro nombre: ");
        LeerTexto(p.nombre, 51);
        printf("\nIngrese el apellido: ");
        LeerTexto(p.apellido, 51);
    }
    fclose(fp);
    return 0;
}

void LeerTexto(char str[], int tam)
{
    int i = 0;
    fflush(stdin);
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