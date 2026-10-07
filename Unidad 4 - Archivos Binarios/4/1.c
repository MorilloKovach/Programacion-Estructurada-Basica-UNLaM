#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int codigo;
    float precio;
    char descripcion[51];
} PRECIOS;

float LeerYValidarIncremento();
void LeerArchivo(FILE *);

int main()
{
    FILE *fp = fopen("PRECIOS.dat", "r+b");
    if (fp == NULL)
    {
        printf("\nError, no se puede abrir el archivo");
        exit(1);
    }
    LeerArchivo(fp);
    fclose(fp);
    return 0;
}

float LeerYValidarIncremento()
{
    float n;
    do
    {
        printf("\nIngrese el porcentaje del incremento: ");
        scanf("%f", &n);
    } while (n <= -0.0);
    return n;
}

void LeerArchivo(FILE *fp)
{
    float inc;
    PRECIOS p;
    inc = LeerYValidarIncremento();
    fread(&p, sizeof(PRECIOS), 1, fp);
    while(!feof(fp))
    {
        printf("\n%.2f %d",p.precio, p.codigo);
        fseek(fp, sizeof(PRECIOS)*-1,SEEK_CUR);
        fwrite(&p, sizeof(PRECIOS), 1, fp);
        fflush(fp);
        fread(&p, sizeof(PRECIOS), 1, fp);
    }
}

/*
1234
2234
8834
2058
9001
4052
7733
2089
7159
*/