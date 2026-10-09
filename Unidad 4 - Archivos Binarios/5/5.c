#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int codigo;
    float precio;
    char descripcion[51];
} PRECIOS;

float LeerYValidarPrecio();
int BuscarYLeerEnArchivo(int, FILE *, PRECIOS *);

int main()
{
    FILE *fp = fopen("PRECIOS.dat", "r+b");
    PRECIOS p;
    int cod;
    float precio;
    int band = 0;
    if (fp == NULL)
    {
        printf("\nError, no se puede abrir el archivo");
        exit(1);
    }
    do
    {
        printf("\nIngrese el codigo (1000-9999): ");
        scanf("%d", &cod);
    } while (!(cod >= 1000 && cod <= 9999));
    while (cod != 0)
    {
        band = BuscarYLeerEnArchivo(cod, fp, &p);
        if (band)
        {
            precio = LeerYValidarPrecio();
            p.precio = precio;
            fseek(fp, (long int)sizeof(PRECIOS) * -1, SEEK_CUR);
            fwrite(&p, sizeof(PRECIOS), 1, fp);
            printf("\nModificado con exito.");
        }
        else
        {
            printf("\nNo se pudo encontrar el registro.");
        }
        do
        {
            printf("\nIngrese el codigo (1000-9999): ");
            scanf("%d", &cod);
        } while (!(cod >= 1000 && cod <= 9999));
        rewind(fp);
    }
    fread(&p, sizeof(PRECIOS), 1, fp);
    while (!feof(fp))
    {
        printf("\n%d %.2f\n", p.codigo, p.precio);
        fread(&p, sizeof(PRECIOS), 1, fp);
    }
    fclose(fp);
    return 0;
}

float LeerYValidarPrecio()
{
    float n;
    do
    {
        printf("\nIngrese el nuevo precio: ");
        scanf("%f", &n);
    } while (n < 0);
    return n;
}

int BuscarYLeerEnArchivo(int cod, FILE *fp, PRECIOS *p)
{
    int band = 0;
    fread(p, sizeof(PRECIOS), 1, fp);
    while (!feof(fp) && !band)
    {
        if (p->codigo == cod)
        {
            band = 1;
        }
        else
        {
            fread(p, sizeof(PRECIOS), 1, fp);
        }
    }
    return band;
}