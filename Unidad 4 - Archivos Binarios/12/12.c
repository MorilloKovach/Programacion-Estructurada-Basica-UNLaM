/*
Se dispone de un archivo con nombre Llamadas.dat que contiene llamadas telefónicas realizadas en una
empresa. Por cada llamada se dispone de la siguiente información:
• Sector (15 caracteres máximo)
• Duración en segundos (entero)
• Tipo de llamada (entero: 1 local, 2 larga distancia, 3 celular)
El archivo se encuentra organizado por Sector. Se solicita:
a. Calcular y mostrar por cada sector, la cantidad de llamadas realizadas de cada tipo.
b. Determinar cuál es el sector que habló la mayor cantidad de tiempo.
c. En un archivo llamado costos.dat hay un único registro que contiene los costos por segundo de los
tres tipos de llamadas (3 float). Se debe generar el archivo gastos.dat que totalice los gastos de
llamadas de cada sector.
d. Realizar una función que muestre los datos almacenados en gastos.dat en forma de listado.
e. Generar un archivo para cada sector con el detalle de llamadas valorizado. El archivo se debe
generar con nombresector.dat y debe contener:
• Duración en segundos (entero)
• Tipo de llamada (entero)
• Costo de la llamada (float)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char sector[16];
    int dur;
    int llamada;
} Sector;

typedef struct
{
    int dur;
    int tipo;
    float costo;
} Llamada;

typedef struct
{
    char sector[16];
    float costo;
} Gasto;

FILE *AbrirArchivo(char[], char[]);

void LlenarLlamadas(float[], FILE *);
FILE *AbrirArchivoSector(char[]);
void MostrarRegistros(FILE *);
void ProcesarLlamadas(FILE *, FILE *, float []);
int main()
{
    float costosLlamadas[3];
    FILE *fpSectores = AbrirArchivo("LLAMADAS.dat", "rb");
    FILE *fpCostos = AbrirArchivo("COSTOS.dat", "rb");
    FILE *fpGenerarGastos = AbrirArchivo("gastos.dat", "w+b");

    LlenarLlamadas(costosLlamadas, fpCostos);
    fclose(fpCostos);

    ProcesarLlamadas(fpSectores, fpGenerarGastos, costosLlamadas);
    MostrarRegistros(fpGenerarGastos);

    fclose(fpGenerarGastos);
    fclose(fpSectores);
    return 0;
}

FILE *AbrirArchivo(char orig[], char mod[])
{
    FILE *fp = fopen(orig, mod);
    if (fp == NULL)
    {
        printf("\nFallo en la ejecucion");
        exit(1);
    }
    return fp;
}

void MostrarRegistros(FILE *fp)
{
    Gasto gastos;
    printf("\nRegistro de los gastos: ");
    fseek(fp, (long)0, SEEK_SET);
    fread(&gastos, sizeof(Gasto), 1, fp);
    printf("\nSECTOR\tCOSTO TOTAL");
    while (!feof(fp))
    {
        printf("\n%s\t%.2f", gastos.sector, gastos.costo);
        fread(&gastos, sizeof(Gasto), 1, fp);
    }
}

void LlenarLlamadas(float costosLlamadas[], FILE *fpCostos)
{
    int i = 0;
    float auxCosto;
    fread(&auxCosto, sizeof(float), 1, fpCostos);
    while (!feof(fpCostos))
    {
        costosLlamadas[i++] = auxCosto;
        fread(&auxCosto, sizeof(float), 1, fpCostos);
    }
}
void ProcesarLlamadas(FILE *fpSectores, FILE *fpGenerarGastos, float costosLlamadas[])
{
    Sector auxSector;
    Llamada llamadas;
    Gasto gastos;
    FILE *fpGenerarArchivos;
    int loc, lardis, cel, tiempo, mejorTiempo = 0, band = 0;
    float costoTot;
    char sec[16], mejorSector[16];

    fread(&auxSector, sizeof(Sector), 1, fpSectores);
    while (!feof(fpSectores))
    {
        strcpy(sec, auxSector.sector);
        loc = 0;
        lardis = 0;
        cel = 0;
        tiempo = 0;
        costoTot = 0;
        fpGenerarArchivos = AbrirArchivoSector(sec);

        while (!feof(fpSectores) && strcmp(sec, auxSector.sector) == 0)
        {
            switch (auxSector.llamada)
            {
            case 1:
                loc++;
                break;
            case 2:
                lardis++;
                break;
            case 3:
                cel++;
                break;
            }

            llamadas.dur = auxSector.dur;
            llamadas.tipo = auxSector.llamada;
            llamadas.costo = costosLlamadas[auxSector.llamada - 1] * auxSector.dur;

            tiempo += llamadas.dur;
            costoTot += llamadas.costo;

            fwrite(&llamadas, sizeof(Llamada), 1, fpGenerarArchivos);
            fread(&auxSector, sizeof(Sector), 1, fpSectores);
        }

        fclose(fpGenerarArchivos);
        printf("\nEn el sector %s se han realizado %d llamadas locales, %d a distancia y %d por celular.", sec, loc, lardis, cel);

        if (band == 0 || tiempo > mejorTiempo)
        {
            band = 1;
            mejorTiempo = tiempo;
            strcpy(mejorSector, sec);
        }

        strcpy(gastos.sector, sec);
        gastos.costo = costoTot;
        fwrite(&gastos, sizeof(Gasto), 1, fpGenerarGastos);
    }

    if (band == 1)
    {
        printf("\nEl sector que mas tiempo tuvo de charla fue: %s\n", mejorSector);
    }
}
FILE *AbrirArchivoSector(char sec[])
{
    FILE *fpGenerarArchivos;
    char archivo[21];
    strcpy(archivo, sec);
    strcat(archivo, ".dat");
    fpGenerarArchivos = AbrirArchivo(archivo, "wb");
    return fpGenerarArchivos;
}