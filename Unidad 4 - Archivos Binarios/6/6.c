#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int codigo;
    float precio;
    char descripcion[51];
} PRECIOS;

int LecturaYEscritura(FILE *, FILE *, PRECIOS *, int);

int main()
{
    FILE *fp;
    FILE *fpMod;
    PRECIOS p;
    int cod;
    int band = 0;
    printf("\nIngrese el codigo: ");
    scanf("%d", &cod);
    while (cod != 0)
    {
        fpMod = fopen("PRECIOS-aux.dat", "w+b");
        fp = fopen("PRECIOS.dat", "r+b");
        if (fpMod == NULL || fp == NULL)
        {
            printf("\nNO SE PUEDEN ABRIR LOS ARCHIVOS");
            exit(1);
        }
        band = LecturaYEscritura(fp, fpMod, &p, cod);
        fclose(fpMod);
        fclose(fp);
        if (band == 1)
        {
            remove("PRECIOS.dat");
            rename("PRECIOS-aux.dat", "PRECIOS.dat");
            printf("\nProducto eliminado con exito.");
        }
        else
        {
            remove("PRECIOS-aux.dat");
            printf("\nError: El producto no existia en el archivo.");
        }
        printf("\nIngrese codigo: ");
        scanf("%d", &cod);
    }
    fp = fopen("PRECIOS.dat", "r+b");
    fread(&p, sizeof(PRECIOS), 1, fp);
    while (!feof(fp))
    {
        printf("\n%d %.2f\n", p.codigo, p.precio);
        fread(&p, sizeof(PRECIOS), 1, fp);
    }
    fclose(fp);
    return 0;
}

int LecturaYEscritura(FILE *fp, FILE *fpMod, PRECIOS *p, int cod)
{
    int band = 0;
    fseek(fp, 0, SEEK_SET);
    fread(p, sizeof(PRECIOS), 1, fp);
    while (!feof(fp))
    {
        if ((p)->codigo != cod)
        {
            fwrite(p, sizeof(PRECIOS), 1, fpMod);
        }
        else
        {
            band = 1;
        }
        fread(p, sizeof(PRECIOS), 1, fp);
    }
    return band;
}