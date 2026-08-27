/*
Se ingresan código y precio unitario de los productos que vende un negocio. No se sabe la cantidad exacta de
productos, pero sí se sabe que son menos de 50. El código es alfanumérico de 3 caracteres y la carga de los
datos de productos termina con un código igual al “FIN”. Luego se registran las ventas del día y por cada venta
se ingresa el código de producto y cantidad de unidades vendidas terminando con una cantidad igual a 0. Se
solicita:
a. Calcular la recaudación total del día y el producto del cual se vendió menor cantidad de unidades.
b. Mostrar el listado de productos con su precio ordenado en forma alfabética por código de producto
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 50
#define ALPHA 4

int CargarProductos(char[][ALPHA], int *, int);
void CargarVentas(char[][ALPHA], int *, int);
int Buscar(char[][ALPHA], char[], int);
void Recaudacion(char[][ALPHA], int*, int*, int);
void Ordenar(char[][ALPHA], int*, int*, int);
void Mostrar(char[][ALPHA], int*, int*, int);
char *LeerValidarCodigo();
int LeerValidarEntero();

int main()
{
    char codigosProductos[TAM][ALPHA];
    int *ventas, *precios, tam,i;
    ventas = calloc(TAM, sizeof(int));
    precios = calloc(TAM, sizeof(int));
    tam = CargarProductos(codigosProductos, precios, TAM);
    printf("\nEMPECEMOS A CARGAR LAS VENTAS\n");
    CargarVentas(codigosProductos, ventas, tam);
    Recaudacion(codigosProductos, precios, ventas, tam);
    Ordenar(codigosProductos, precios, ventas, tam);
    Mostrar(codigosProductos, precios, ventas, tam);
    free(ventas);
    free(precios);
    return 0;
}

void CargarVentas(char productos[][ALPHA], int *ventas, int tam)
{
    char *prod;
    int cant_ventas, idx;
    do
    {
        prod = LeerValidarCodigo();
        idx = Buscar(productos, prod, tam);
    } while (idx == -1);
    cant_ventas = LeerValidarEntero();
    while (cant_ventas != 0)
    {
        free(prod);
        ventas[idx] += cant_ventas;
        do
        {
            prod = LeerValidarCodigo();
            idx = Buscar(productos, prod, tam);
        } while (idx == -1);
        cant_ventas = LeerValidarEntero();
    }
}

int CargarProductos(char productos[][ALPHA], int *precios, int tam)
{
    int i = 0;
    char *prod;
    prod = LeerValidarCodigo();
    printf("%s",prod);
    while (strcmp(prod, "FIN") != 0 && i < tam)
    {
        precios[i] = LeerValidarEntero();
        strcpy(productos[i], prod);
        i++;
        prod = LeerValidarCodigo();
    }
    return i;
}

int Buscar(char productos[][ALPHA], char cod[], int tam)
{
    int i = 0, idx = -1;
    while (i < tam && idx == -1)
    {
        if (strcmp(productos[i], cod) == 0)
        {
            idx = i;
        }
        else
            i++;
    }
    return idx;
}

int LeerValidarEntero()
{
    int p;
    do
    {
        printf("\nIngrese el dato entero (positivo o 0): ");
        scanf("%d", &p);
    } while (p < 0);
    return p;
}

char *LeerValidarCodigo()
{
    char *cod;
    cod = calloc(ALPHA, sizeof(char));
    do
    {
        printf("\nIngrese el codigo del producto: ");
        scanf("%s", cod);
    } while (strlen(cod) != 3);
    return cod;
}
void Ordenar(char productos[][ALPHA], int *precios, int* ventas, int tam)
{
    int i, j, auxInt;
    char *cod;
    cod = calloc(ALPHA, sizeof(char));
    for(i=0;i<tam-1;i++)
    {
        for(j=0;j<tam-i-1; j++)
        {
            if(strcmp(productos[j], productos[j+1]) > 0)
            {
                strcpy(cod, productos[j]);
                strcpy(productos[j], productos[j+1]);
                strcpy(productos[j+1], cod);

                auxInt = *(precios+j);
                *(precios+j) = *(precios+j+1);
                *(precios+j+1) = auxInt;

                auxInt = *(ventas+j);
                *(ventas+j) = *(ventas+j+1);
                *(ventas+j+1) = auxInt;
            }
        }
    }
}

void Recaudacion(char productos[][ALPHA], int *precios, int *ventas, int tam)
{
    int i, min, flag=0,tot=0;
    char *cod;
    cod = calloc(ALPHA, sizeof(char));
    for(i=0; i<tam; i++)
    {
        if(*(ventas+i)>0 && (!flag || min > *(ventas+i))){
            min = *(ventas+i);
            strcpy(cod, productos[i]);
            flag = 1;
        }
        tot+=*(ventas+i) * *(precios+i);
    }
    printf("\nEl total vendido es %d y el codigo con menos ventas es %s\n",tot,cod);
}

void Mostrar(char productos[][ALPHA], int* precios, int* ventas, int tam)
{
    int i;
    for(i=0;i<tam; i++)
    {
        printf("\n%s vendio %d unidades y en total recaudo %d\n", productos[i], *(ventas+i), *(precios+i) * *(ventas+i));
    }
}
