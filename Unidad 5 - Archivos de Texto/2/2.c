#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *AbrirArchivo(char[], char[]);
void RomperSiFalla(void *);
void RealizarLectura(FILE *, char[], int);
int main()
{
    FILE *fp = AbrirArchivo("cadenas.txt", "r");
    char str[300];
    RealizarLectura(fp, str, 300);
    fclose(fp);
    return 0;
}

void RealizarLectura(FILE *fp, char str[], int tam)
{
    while (fgets(str, tam, fp))
    {
        printf("%s", str);
    }
}

FILE *AbrirArchivo(char nom[], char mod[])
{
    FILE *fp = fopen(nom, mod);
    RomperSiFalla(fp);
    return fp;
}

void RomperSiFalla(void *ptr)
{
    if (ptr == NULL)
    {
        printf("\nError en la ejecucion");
        system("pause");
        exit(1);
    }
}