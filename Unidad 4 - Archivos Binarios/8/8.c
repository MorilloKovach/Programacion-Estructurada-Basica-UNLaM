/*

8. Se dispone de un archivo que contiene información de los vuelos realizados por las distintas aerolíneas a
lo largo del mes. El archivo se denomina Vuelos.dat y guarda los registros con la siguiente estructura:
• Código Aerolínea (alfanumérico de 10 caracteres máximo)
• Día (entero)
• Número de Vuelo (entero)
• Costo del pasaje (real)
 Pasajeros (inicialmente en el archivo viene en 0)
Luego se dispone de un segundo archivo llamado Pasajeros.dat que incluye la información de los viajeros
del mes para la aerolínea con código “Aero1”, el archivo contiene los siguientes campos:
• DNI (entero)
• Número de Vuelo (entero)
Se desea realizar un programa que actualice la cantidad de pasajeros de la aerolínea con código “Aero1”
con la información de los pasajeros que realizaron los viajes. Tenga en cuenta que los números de vuelo se
repiten entre las distintas aerolíneas.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char codigo[11];
    int dia;
    int num_vuelo;
    float costo;
    int pasajeros;
} VUELOS;

typedef struct
{
    int DNI;
    int num_vuelo;
} PASAJEROS;

FILE *abrir_archivo(char[], char[]);
VUELOS *LeerVuelos(FILE *, int *);
void ActualizarPasajerosEnMemoria(FILE *, VUELOS *, int);
void ActualizarVuelos(FILE *, VUELOS *, int);
int BuscarVuelo(VUELOS *, int, int);
void RomperSiFalla(void *);
int main()
{
    FILE *fpVuelos = abrir_archivo("VUELOS.dat", "r+b");
    FILE *fpPasajeros = abrir_archivo("PASAJEROS.dat", "rb");
    VUELOS *v = NULL, aux;
    int tam = 0;

    v = LeerVuelos(fpVuelos, &tam);

    if (tam > 0)
    {
        printf("\nActualizando registros.");

        ActualizarPasajerosEnMemoria(fpPasajeros, v, tam);
        ActualizarVuelos(fpVuelos, v, tam);

        printf("\nActualizacion exitosa.");
    }
    else
    {
        printf("\nNo se encontraron registros de la Aerolinea AERO1. Cerrando el programa");
    }

    free(v);
    fclose(fpPasajeros);
    fclose(fpVuelos);

    return 0;
}

void RomperSiFalla(void *ptr)
{
    if (ptr == NULL)
    {
        printf("\nERROR EN LA EJECUCION");
        exit(1);
    }
}
FILE *abrir_archivo(char arch[], char mod[])
{
    FILE *fp = fopen(arch, mod);
    RomperSiFalla(fp);

    return fp;
}
VUELOS *LeerVuelos(FILE *fp, int *tam)
{
    VUELOS *v = NULL, *aux, vuelo;

    fread(&vuelo, sizeof(VUELOS), 1, fp);
    while (!feof(fp))
    {
        if (strcmp("AERO1", vuelo.codigo) == 0)
        {

            aux = (VUELOS *)realloc(v, ((*tam) + 1) * sizeof(VUELOS));
            RomperSiFalla(aux);
            v = aux;
            *(v + (*tam)) = vuelo;
            (*tam)++;
        }
        fread(&vuelo, sizeof(VUELOS), 1, fp);
    }
    return v;
}

int BuscarVuelo(VUELOS *v, int tam, int num_viaje)
{
    int idx = -1, i = 0;

    while (i < tam && idx == -1)
    {
        if ((v + i)->num_vuelo == num_viaje)
        {
            idx = i;
        }
        else
        {
            i++;
        }
    }
    return idx;
}

void ActualizarPasajerosEnMemoria(FILE *fp, VUELOS *v, int tam)
{
    PASAJEROS p;
    int idx;
    fread(&p, sizeof(PASAJEROS), 1, fp);

    while (!feof(fp))
    {
        idx = BuscarVuelo(v, tam, p.num_vuelo);

        if (idx == -1)
        {
            printf("\nNo se cuenta este viaje, no se pudo encontrar el vuelo.");
        }
        else
        {
            (v + idx)->pasajeros++;
            printf("\nModificacion hecha con exito, numero de vuelo: %d\n", p.num_vuelo);
        }

        fread(&p, sizeof(PASAJEROS), 1, fp);
    }
}

void ActualizarVuelos(FILE *fp, VUELOS *v, int tam)
{
    int idx;
    VUELOS aux;

    rewind(fp);
    fread(&aux, sizeof(VUELOS), 1, fp);
    while (!feof(fp))
    {
        if (strcmp(aux.codigo, "AERO1") == 0)
        {
            idx = BuscarVuelo(v, tam, aux.num_vuelo);
            fseek(fp, (long int)sizeof(VUELOS) * -1, SEEK_CUR);
            fwrite((v + idx), sizeof(VUELOS), 1, fp);
            fflush(fp);
        }

        fread(&aux, sizeof(VUELOS), 1, fp);
    }
}