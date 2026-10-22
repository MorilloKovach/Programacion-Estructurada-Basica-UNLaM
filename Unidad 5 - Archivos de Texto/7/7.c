/*
EJERCICIO 7 - UNIDAD 5
Dado un archivo ventas.csv con ventas de productos que contiene producto;precio;cantidad;sucursal siendo
• Producto un string correspondiente al código de producto de máximo 10 caracteres
• Precio un valor real con el precio unitario el producto
• Cantidad la cantidad de productos vendida (entero)
• Sucursal, el código la sucursal de la venta (entero)
Calcular:
• La cantidad total de ventas realizadas
• La cantidad total de productos vendidos
• El importe total vendido por cada sucursal (usar un vector dinámico en memoria que pueda ir
creciendo para guarda estar información)
• Generar un archivo resumenVenta.txt que contenga, la información de los 3 items anteriores
Nota: para realizar los cálculos debe recuperar cada registro del archivo y pasarlo a una estructura en
memoria
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char producto[11];
    float precio;
    int cantidad;
    int cod_sucursal;
} Productos;

typedef struct
{
    int sucursal;
    float total_imp;
} Archivo;

int BuscarMemoria(Archivo *, int, int);
void TocarSector(Productos *, char *, int);
Archivo *Generar(FILE *, int *, int *, int *);
void EscribirEnArchivo(FILE *, Archivo *, int, int, int);
FILE *AbrirArchivo(char[], char[]);
void RomperAlFallo(void *);
Archivo *ActualizarSucursal(Archivo *, int *, int, float);
void ObtenerProd(Productos *, char []);
int main()
{
    Archivo *a;
    FILE *fp = AbrirArchivo("ventas.csv", "r");
    FILE *fpMod = AbrirArchivo("resumenVenta.txt", "w");

    int cant = 0, productosVendidos = 0, tam = 0;
    a = Generar(fp, &productosVendidos, &cant, &tam);

    EscribirEnArchivo(fpMod, a, tam, productosVendidos, cant);

    fclose(fp);
    fclose(fpMod);
    free(a);
    return 0;
}

void RomperAlFallo(void *ptr)
{
    if (ptr == NULL)
    {
        printf("\nError en la ejecucion");
        system("pause");
        exit(1);
    }
}

FILE *AbrirArchivo(char nom[], char mod[])
{
    FILE *fp = fopen(nom, mod);
    RomperAlFallo(fp);
    return fp;
}

void TocarSector(Productos *d, char *s, int p)
{
    float flotante;
    int entero;
    switch (p)
    {
    case 1:
        strcpy(d->producto, s);
        break;
    case 2:
        flotante = atof(s);
        d->precio = flotante;
        break;
    case 3:
        entero = atoi(s);
        d->cantidad = entero;
        break;
    default:
        entero = atoi(s);
        d->cod_sucursal = entero;
        break;
    }
}
int BuscarMemoria(Archivo *a, int cod, int tam)
{
    int i = 0, pos = -1;
    while (i < tam && pos == -1)
    {
        if ((a + i)->sucursal == cod)
        {
            pos = i;
        }
        else
        {
            i++;
        }
    }
    return pos;
}
Archivo *ActualizarSucursal(Archivo *a, int *tam, int cod_sucursal, float importe)
{
    int idx = BuscarMemoria(a, cod_sucursal, *tam);
    Archivo *aux;

    if (idx == -1)
    {
        aux = (Archivo *)realloc(a, ((*tam) + 1) * sizeof(Archivo));
        RomperAlFallo(aux);
        a = aux;
        (a + (*tam))->sucursal = cod_sucursal;
        (a + (*tam))->total_imp = importe;
        (*tam)++;
    }
    else
    {
        (a + idx)->total_imp += importe;
    }

    return a;
}

void ObtenerProd(Productos *p, char linea[])
{
    int pos;
    char *parte;
    pos = 1;
    parte = strtok(linea, ";\n");
    while (parte != NULL)
    {
        TocarSector(p, parte, pos);
        parte = strtok(NULL, ";\n");
        pos++;
    }
}

Archivo *Generar(FILE *fp, int *productosVendidos, int *cant, int *t)
{
    Productos p;
    Archivo *a = NULL;
    char linea[300];
    while (fgets(linea, 300, fp))
    {
        ObtenerProd(&p, linea);
        (*cant)++;
        (*productosVendidos) += p.cantidad;
        a = ActualizarSucursal(a, t, p.cod_sucursal, p.precio * p.cantidad);
    }
    return a;
}

void EscribirEnArchivo(FILE *fpMod, Archivo *a, int tam, int productosVendidos, int cant)
{
    int pos;
    fprintf(fpMod, "Cantidad de ventas: %d", cant);
    fprintf(fpMod, "\nCantidad de productos vendidos: %d", productosVendidos);
    for (pos = 0; pos < tam; pos++)
    {
        fprintf(fpMod, "\nSucursal %d importe total %.2f", (a + pos)->sucursal, (a + pos)->total_imp);
    }
}