/*
5. Una empresa de alquiler de autos tiene una flota de 30 autos de alta gama, identificados por su número de
patente, cargado en la memoria principal en un vector de 30 posiciones. Al comenzar el procesamiento de
los alquileres, se ingresa la fecha y la cotización del dólar de ese día. A continuación, se ingresan los siguientes
datos correspondiente a cada alquiler realizado en el día:
• Patente del auto (alfanumérico, de 6 caracteres)
• Cantidad de días de alquiler (entero, mayor que 0)
• Precio diario del alquiles en dólares (real, mayor que 0)
Para finalizar la carga del día, se ingresa una patente de auto igual a “FINDIA”
Determinar e informar:
a. El porcentaje de autos alquilados durante el día.
b. Realizar el informe con el formato siguiente:
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 30
#define ALPHA 7

int fecha(int, int, int);
int esMes31(int);
int esBisiesto(int);
void MoverFecha(int *, int *, int *, int);
char *cargaCodigo(int);
int cargaDias();
float cargaCosto();
int cargaDatos(char[][ALPHA], int *, float *, int);
float porcentaje(int, int);
int main()
{
    int dia, mes, anio, *diasAlquiler, tam, i;
    char cod[TAM][ALPHA];
    float dolar, *costo_alquiler, tot = 0;
    diasAlquiler = calloc(TAM, sizeof(int));
    costo_alquiler = calloc(TAM, sizeof(float));
    do
    {
        printf("\nIngrese el dia: ");
        scanf("%d", &dia);
        printf("\nIngrese el mes: ");
        scanf("%d", &mes);
        printf("\nIngrese el anio: ");
        scanf("%d", &anio);
    } while (!fecha(dia, mes, anio));
    printf("\nIngrese la cotizacion del dolar: ");
    scanf("%f", &dolar);
    tam = cargaDatos(cod, diasAlquiler, costo_alquiler, TAM);
    int dAux, mAux, aAux;
    printf("\nEl porcentaje de los vehiculos alquilados fue %.2f\n", porcentaje(tam, TAM));
    printf("\nALQUILER DE AUTOS DEL DÍA: %d-%d-%d COTIZACION DEL DÓLAR: $ %.2f\n", dia, mes, anio, dolar);
    printf("\nNRO. DE AUTO\tDIAS DE ALQUILER\tPRECIO DE ALQUILER EN PESOS POR DIA\t FECHA DE DEVOLUCION\n");
    for (i = 0; i < tam; i++)
    {
        dAux = dia;
        mAux = mes;
        aAux = anio;
        tot += *(costo_alquiler + i) * *(diasAlquiler + i);
        MoverFecha(&dAux, &mAux, &aAux, *(diasAlquiler + i));
        printf("\n%s \t %d \t %.2f \t %d/%d/%d", cod[i], *(diasAlquiler + i), *(costo_alquiler + i) * dolar, dAux, mAux, aAux);
    }
    printf("\nEl total en dolares es: $ %.2f", tot);
    printf("\nEl total en pesos es $ %.2f", tot * dolar);
    free(costo_alquiler);
    free(diasAlquiler);
    return 0;
}

int cargaDatos(char patentes[][ALPHA], int *dias, float *costo, int tam)
{
    int i, dia;
    char *cod;
    float cost;
    i = 0;
    cod = cargaCodigo(ALPHA);
    while (strcmp(cod, "FINDIA") != 0 && i < tam)
    {
        cost = cargaCosto();
        dia = cargaDias();
        strcpy(patentes[i], cod);
        *(dias + i) = dia;
        *(costo + i) = cost;
        free(cod);
        cod = cargaCodigo(ALPHA);
        i++;
    }
    free(cod);
    return i;
}

float porcentaje(int tam, int tam_max)
{
    float calc = (float)tam / (float)tam_max * 100.0;
    return calc;
}

int cargaDias()
{
    int dia;
    do
    {
        printf("\nIngrese la cantidad de dias a alquilar: ");
        scanf("%d", &dia);
    } while (dia <= 0);
    return dia;
}

float cargaCosto()
{
    float costo;
    do
    {
        printf("\nIngrese el costo del auto: ");
        scanf("%f", &costo);
    } while (costo <= 0);
    return costo;
}

char *cargaCodigo(int car)
{
    char *cod;
    cod = calloc(car, sizeof(char));
    do
    {
        printf("\nIngrese el codigo del auto: ");
        scanf("%s", cod);
    } while (strlen(cod) != car-1);
    return cod;
}
void MoverFecha(int *d, int *m, int *a, int dias)
{
    int i;
    int dia = *d, mes = *m, anio = *a;
    for (i = 0; i < dias; i++)
    {
        if (mes == 2)
        {
            if (dia == 28 && !esBisiesto(anio))
            {
                dia = 1;
                mes = 3;
            }
            else
            {
                if ((dia == 28 && esBisiesto(anio)) || dia < 28)
                {
                    dia++;
                }
                else{
                    if(dia==29)
                    {
                        mes++;
                        dia = 1;
                    }
                }
            }
        }
        else
        {
            if (esMes31(mes))
            {
                if (dia == 31)
                {
                    dia = 1;
                    if (mes == 12)
                    {
                        mes = 1;
                        anio++;
                    }
                    else
                    {
                        mes++;
                    }
                }
                else
                {
                    dia++;
                }
            }
            else
            {
                if (dia == 30)
                {
                    dia = 1;
                    mes++;
                }
                else
                {
                    dia++;
                }
            }
        }
    }
    *d = dia;
    *m = mes;
    *a = anio;
}
int esBisiesto(int anio)
{
    int flag = 0;
    if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0)
    {
        flag = 1;
    }
    return flag;
}

int esMes31(int mes)
{
    int flag = 1;
    if ((mes <= 6 && mes % 2 == 0) || (mes > 8 && mes % 2 == 1))
    {
        flag = 0;
    }
    return flag;
}

int fecha(int dia, int mes, int anio)
{
    int flag = 1;
    if (dia < 1 || mes < 1 || anio < 1)
    {
        flag = 0;
    }
    else
    {
        if (mes == 2 && dia > 29)
        {
            flag = 0;
        }
        else
        {
            if (mes == 2 && dia == 29 && !esBisiesto(anio))
            {
                flag = 0;
            }
            else
            {
                if (!esMes31(mes) && dia >= 31)
                {
                    flag = 0;
                }
                else
                {
                    if (esMes31(mes) && dia > 31)
                    {
                        flag = 0;
                    }
                }
            }
        }
    }
    return flag;
}