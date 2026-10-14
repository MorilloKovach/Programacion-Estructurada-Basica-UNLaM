/*
Se dispone de un archivo llamado Stock.dat que contiene la información de los productos que vende una
fábrica. En el archivo se guarda:
• Código de artículo (entero)
• Descripción (50 caracteres máximo)
• Stock (entero)
Luego se ingresan por teclado las ventas a realizar indicando:
• Código de artículo
• Cantidad
 La carga por teclado de las ventas finaliza con un código de artículo igual a 0.
Por cada venta se debe controlar si hay stock suficiente y si lo hay, restar el stock de dicho producto, sino
hay stock se debe vender lo que quede disponible y grabar un registro en un archivo Faltantes.dat con la
cantidad que no pudo venderse, dicho registro debe contener:
• Código de artículo
• Cantidad faltante
Si ya hay un registro previo en dicho archivo de faltantes con el mismo producto debe incrementarse la
cantidad.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int codigo;
    char desc[51];
    int stock;
} Productos;

typedef struct
{
    int cod;
    int cantidad;
} Faltantes;

void ActualizarFaltantes(FILE *, Faltantes *, int, int);
int BuscarFaltante(FILE *, Faltantes *, int);
void RealizarLectura(FILE *, FILE *);
int BuscarEnArchivo(FILE *, Productos *, int);
int LeerYValidarCodigo(int, int, int);
void AgregarEnFaltantes(FILE *, FILE *, Productos *, Faltantes *, int, int);
int main()
{
    FILE *fpLec, *fpVta;
    fpLec = fopen("STOCK.dat", "r+b");
    fpVta = fopen("FALTANTES.dat", "w+b");
    if (fpLec == NULL || fpVta == NULL)
    {
        printf("\nNo se pudo abrir el archivo.");
        exit(1);
    }
    RealizarLectura(fpLec, fpVta);
    fclose(fpLec);
    fclose(fpVta);
    return 0;
}

void AgregarEnFaltantes(FILE *fpLec, FILE *fpVta, Productos *p, Faltantes *f, int cantQuePaso, int cod)
{
    p->stock = 0;
    fseek(fpLec, (long)sizeof(Productos) * -1, SEEK_CUR);
    fwrite(p, sizeof(Productos), 1, fpLec);
    f->cantidad = cantQuePaso;
    f->cod = cod;
    fseek(fpVta, (long)0, SEEK_END);
    fwrite(f, sizeof(Faltantes), 1, fpVta);
}

void ActualizarFaltantes(FILE *fpVta, Faltantes *f, int cod, int cantidadFaltante)
{
    fseek(fpVta, (long)sizeof(Faltantes) * -1, SEEK_CUR);
    f->cantidad += cantidadFaltante;
    fwrite(f, sizeof(Faltantes), 1, fpVta);
    fseek(fpVta, 0L, SEEK_END);
}

int BuscarFaltante(FILE *fpVta, Faltantes *f, int cod)
{
    int band = 0;
    rewind(fpVta);
    fread(f, sizeof(Faltantes), 1, fpVta);
    while (!feof(fpVta) && band == 0)
    {
        if (f->cod == cod)
        {
            band = 1;
        }
        else
        {
            fread(f, sizeof(Faltantes), 1, fpVta);
        }
    }
    return band;
}
int BuscarEnArchivo(FILE *fp, Productos *p, int cod)
{
    int band = 0;
    fread(p, sizeof(Productos), 1, fp);
    while (!feof(fp) && !band)
    {
        if (p->codigo == cod)
        {
            band = 1;
        }
        else
        {
            fread(p, sizeof(Productos), 1, fp);
        }
    }
    return band;
}
int LeerYValidarCodigo(int linf, int lsup, int corte)
{
    int codigo;
    do
    {
        printf("\nIngrese el codigo (entre 1000 a 9999): ");
        scanf("%d", &codigo);
    } while ((codigo < linf || codigo > lsup) && codigo != corte);
    return codigo;
}
void RealizarLectura(FILE *fpLec, FILE *fpVta)
{
    Productos p;
    Faltantes f;
    int cod, cantidad, band;
    cod = LeerYValidarCodigo(1000, 9999, 0);
    while (cod != 0)
    {
        do
        {
            printf("\nIngrese la cantidad: ");
            scanf("%d", &cantidad);
        } while (cantidad <= 0);
        rewind(fpLec);
        band = BuscarEnArchivo(fpLec, &p, cod);
        if (band)
        {
            if (p.stock >= cantidad)
            {
                p.stock -= cantidad;
                fseek(fpLec, (long)sizeof(Productos) * -1, SEEK_CUR);
                fwrite(&p, sizeof(Productos), 1, fpLec);
            }
            else
            {
                if (!BuscarFaltante(fpVta, &f, cod))
                {
                    AgregarEnFaltantes(fpLec, fpVta, &p, &f, cantidad - p.stock, cod);
                }
                else
                {
                    ActualizarFaltantes(fpVta, &f, cod, cantidad);
                }
            }
        }
        else
        {
            printf("\nNo existe ese codigo en los ficheros....");
        }
        cod = LeerYValidarCodigo(1000, 9999, 0);
    }
    printf("\nCerrando la lectura.");
}