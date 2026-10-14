/*
Se desea realizar un programa que permita actualizar la lista de precios de una empresa en forma
individual a cada uno de sus productos.
Los productos que están guardados en el archivo productos.dat con la siguiente estructura:
• Código (entero)
• Precio (float)
• Descripción (de hasta 50 caracteres)
Para modificar un precio se ingresa por teclado el código del producto y el nuevo precio. La modificación
de precios finaliza con un código de producto igual a 0. 
*/

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
int LeerYValidarCodigo(int, int, int);

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
    cod = LeerYValidarCodigo(1000, 9999, 0);
    while (cod != 0)
    {
        band = BuscarYLeerEnArchivo(cod, fp, &p);
        if (band)
        {
            precio = LeerYValidarPrecio();
            p.precio = precio;
            fseek(fp, (long)sizeof(PRECIOS) * -1, SEEK_CUR);
            fwrite(&p, sizeof(PRECIOS), 1, fp);
            printf("\nModificado con exito.");
        }
        else
        {
            printf("\nNo se pudo encontrar el registro.");
        }
        cod = LeerYValidarCodigo(1000, 9999, 0);
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

int LeerYValidarCodigo(int linf, int lsup, int corte)
{
    int cod;
    do
    {
        printf("\nIngrese el codigo (%d-%d): ", linf, lsup);
        scanf("%d", &cod);
    } while ((cod < linf || cod > lsup) && cod != corte);
    return cod;
}