#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void LeerTexto(char[], int);
FILE *AbrirArchivo(char[], char[]);
void RomperSiFalla(void *);
void RealizarLectura(FILE *, char[], int);

int main()
{
    FILE *fp = AbrirArchivo("cadenas.txt", "w");
    char str[300];
    RealizarLectura(fp, str, 300);
    return 0;
}

void LeerTexto(char str[], int tam)
{
    int i = 0;
    fflush(stdin);
    fgets(str, tam, stdin);
}

void RealizarLectura(FILE *fp, char str[], int tam)
{
    LeerTexto(str, tam);
    while (strcmp("FINALIZAR\n", str) != 0)
    {
        fputs(str, fp);
        LeerTexto(str, tam);
    }
}

FILE *AbrirArchivo(char nom[], char mod[])
{
    FILE *fp = fopen(nom, mod);
    RomperSiFalla(fp);
    return fp;
}

void RomperSiFalla(void * ptr)
{
    if(ptr==NULL)
    {
        printf("\nError en la ejecucion");
        system("pause");
        exit(1);
    }
}