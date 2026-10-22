/*
Dada una URL estándar como https://usuarios.com, extraer el protocolo (sin ://) y el nombre del
dominio (detenerse en los dos puntos), ignorando el resto de la ruta.
*/

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct
{
    char protocolo[7];
    char web[100];
} Datos;

void LeerTexto(char[], int);

void tocarSector(Datos *, char *, int);

int main()
{
    Datos d;
    FILE *fp = fopen("URL.txt", "r");
    char *parte;
    char linea[300];
    int part;
    while(fgets(linea, 300, fp))
    {
        parte = strtok(linea, "://");
        part = 1;
        while(parte != NULL)
        {
            tocarSector(&d, parte, part);
            parte = strtok(NULL, "://");
            part++;
        }
        printf("\n%s %s\n", d.protocolo, d.web);
    }
    fclose(fp);

    return 0;
}
void tocarSector(Datos *d, char *s, int p)
{
    if(p == 1)
    {
        strcpy(d->protocolo, s);
    }
    else
    {
        strcpy(d->web, s);
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