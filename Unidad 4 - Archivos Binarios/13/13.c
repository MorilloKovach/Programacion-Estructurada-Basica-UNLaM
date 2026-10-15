/*
La empresa RED VIAL S.A. desea controlar el flujo vehicular en sus cabinas de peaje a lo largo del mes.
Para ello se debe procesar la información provista por las barreras que se encuentra almacenada en el
archivo barreras.dat que contiene la siguiente información:
• Día (entero)
• Hora (0 a 24)
• Número de barrera (entero)
Dentro del archivo la información se encuentra ordenada por día y hora. Determinar:
a. La cantidad de vehículos por cada hora.
b. La cantidad de vehículos de cada día.
c. Ingresar por teclado los precios del peaje para horario normal y horario pico (de 7 a 11 y de 17 a
19). Con esos valores guardar un archivo con la recaudación de cada día.
*/

#include <stdio.h>
#include <stdlib.h>

FILE *AbrirArchivo(char[], char[]);
void RomperSiFalla(void *ptr);
void ProcesarPeajes(float *, float *);
void CantidadVehiculos(FILE *, FILE *, float, float);
int ValidarRango(int);
float RealPositivo();
typedef struct
{
    int dia;
    int hora;
    int NumBarrera;
} Barreras;

typedef struct
{
    int dia;
    float costo;
} CostoDia;

int main()
{
    FILE *fpBarreras = AbrirArchivo("barreras.dat", "rb");
    FILE *fpPeajes = AbrirArchivo("peajes.dat", "wb");
    float PeajeNormal, PeajePico;

    ProcesarPeajes(&PeajeNormal, &PeajePico);
    CantidadVehiculos(fpBarreras, fpPeajes, PeajeNormal, PeajePico);

    fclose(fpBarreras);
    fclose(fpPeajes);
    return 0;
}

int ValidarRango(int num)
{
    int band = 1;
    if ((num >= 7 && num <= 11) || (num >= 17 && num <= 19))
    {
        band = 2;
    }
    return band;
}

void RomperSiFalla(void *ptr)
{
    if (ptr == NULL)
    {
        printf("\nError en la ejecucion");
        exit(1);
    }
}

FILE *AbrirArchivo(char nom[], char mod[])
{
    FILE *fp = fopen(nom, mod);
    RomperSiFalla(fp);
    return fp;
}

float RealPositivo()
{
    float num;
    do
    {
        printf("\nIngrese un valor positivo: ");
        scanf("%f", &num);
    } while (num <= 0);
    return num;
}

void ProcesarPeajes(float *precioNormal, float *precioPico)
{
    printf("\nIngrese el precio para el horario normal: ");
    *precioNormal = RealPositivo();
    printf("\nIngrese el precio para la hora pico: ");
    *precioPico = RealPositivo();
}

void CantidadVehiculos(FILE *fpBarreras, FILE *fpPeajes, float precioNormal, float precioPico)
{
    int cantHora, cantDia = 0, band;
    float CostoAcumulado = 0;
    CostoDia cd;
    Barreras barreraActual, barreraPreviaHora, barreraPreviaDia;
    fread(&barreraActual, sizeof(Barreras), 1, fpBarreras);

    barreraPreviaHora = barreraActual;
    barreraPreviaDia = barreraActual;
    
    while (!feof(fpBarreras))
    {
        cantDia = 0;
        barreraPreviaDia = barreraActual;
    
        while (!feof(fpBarreras) && barreraPreviaDia.dia == barreraActual.dia)
        {
            cantHora = 0;
            barreraPreviaHora = barreraActual;
    
            while (!feof(fpBarreras) && barreraPreviaHora.dia == barreraActual.dia && barreraPreviaHora.hora == barreraActual.hora)
            {
                cantHora++;
                fread(&barreraActual, sizeof(Barreras), 1, fpBarreras);
            }
    
            cantDia+=cantHora;
            band = ValidarRango(barreraPreviaHora.hora);
    
            if (band == 1)
            {
                CostoAcumulado += precioNormal * cantHora;
            }
            else
            {
                CostoAcumulado += precioPico * cantHora;
            }

            printf("\nEn el dia %d a las %dhs pasaron %d autos", barreraPreviaHora.dia, barreraPreviaHora.hora, cantHora);
        }

        printf("\nEn el dia %d pasaron %d autos", barreraPreviaDia.dia, cantDia);
        
        cd.dia = barreraPreviaDia.dia;
        cd.costo = CostoAcumulado;
        fwrite(&cd, sizeof(CostoDia), 1, fpPeajes);
        
        CostoAcumulado = 0;
    }
}