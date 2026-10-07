// Este es un programa para simular el ingreso de datos en ventas.dat.

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int mes;
    int anio;
    int dia;
    int codprod;
    float importe;
} ventas;

typedef struct
{
    int dia;
    int mes;
    int anio;
} fecha;

fecha LeerYValidarFecha();
int esMes31(int);
int esBisiesto(int);
int LeerYValidarDia();
int LeerYValidarMes();
int LeerYValidarAnio();
float LeerYValidarImporte();
ventas CargaIndividual(int);
int main()
{
    ventas *a, *aux;
    int i = 0, cod;
    FILE *fp = fopen("ventas.dat", "wb");
    if(fp==NULL)
    {
        printf("\nNO SE PUEDE ABRIR EL ARCHIVO");
        exit(1);
    }
    a = NULL;
    printf("\nIngrese cod: ");
    scanf("%d", &cod);
    while (cod != 0)
    {
        aux = (ventas *)realloc(a, (i + 1) * sizeof(ventas));
        if (aux == NULL)
        {
            printf("\nNo se puede asignar elementos. Cerrando");
            exit(1);
        }
        a = aux;
        *(a + i) = CargaIndividual(cod);
        fwrite(a + i, sizeof(ventas), 1, fp);
        i++;
        printf("\nIngrese otro codigo (o 0 para terminar): ");
        scanf("%d", &cod);
    }
    fclose(fp);
    free(a);
    return 0;
}

int esMes31(int mes)
{
    int band = 0;
    if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
    {
        band = 1;
    }
    return band;
}

int esBisiesto(int anio)
{
    int band = 0;
    if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0)
    {
        band = 1;
    }
    return band;
}

int LeerYValidarDia()
{
    int dia;
    do
    {
        printf("\nIngrese un dia: ");
        scanf("%d", &dia);
    } while (dia < 1 || dia > 31);
    return dia;
}

int LeerYValidarMes()
{
    int mes;
    do
    {
        printf("\nIngrese un mes: ");
        scanf("%d", &mes);
    } while (mes < 1 || mes > 12);
    return mes;
}

int LeerYValidarAnio()
{
    int anio;
    do
    {
        printf("\nIngrese el anio entre 2014 y 2023: ");
        scanf("%d", &anio);
    } while (anio < 2014 || anio > 2023);
    return anio;
}

fecha LeerYValidarFecha()
{
    int band;
    fecha f1;
    do
    {
        band = 1;
        f1.dia = LeerYValidarDia();
        f1.mes = LeerYValidarMes();
        f1.anio = LeerYValidarAnio();
        if (f1.dia == 31 && !esMes31(f1.mes))
        {
            band = 0;
        }
        else
        {
            if (f1.dia == 30 && !esMes31(f1.mes) && f1.mes == 2)
            {
                band = 0;
            }
            else
            {
                if (f1.dia == 29 && f1.mes == 2 && !esBisiesto(f1.anio))
                {
                    band = 0;
                }
            }
        }
    } while (!band);
    return f1;
}

float LeerYValidarImporte()
{
    float importe;
    do
    {
        printf("\nIngrese el valor del importe: ");
        scanf("%f", &importe);
    } while (importe < 0);
    return importe;
}

ventas CargaIndividual(int cod)
{
    fecha f1;
    ventas vta;
    f1 = LeerYValidarFecha();
    vta.codprod = cod;
    vta.dia = f1.dia;
    vta.mes = f1.mes;
    vta.anio = f1.anio;
    vta.importe = LeerYValidarImporte();
    return vta;
}