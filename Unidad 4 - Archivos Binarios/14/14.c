#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int interno;
    int tarjeta;
    char cod[11];
    int dia;
    int hora;
} SUBE;

typedef struct
{
    int mes;
    char cod[11];
    float precio;
} TARIFAS;

typedef struct
{
    int interno;
    int cant;
    float costo;
} VIAJES_TARIFAS;

typedef struct
{
    int interno;
    char cod[11];
    int cant;
} VIAJES_TOT;

TARIFAS *CargaTarifas(FILE *, int, int *);
void OrdenarViajes(VIAJES_TOT *, int);
int BuscarEnMemoria(VIAJES_TOT *vt, int, char[]);
void MostrarViajes(FILE *);
float CalcularImporte(FILE *, TARIFAS *, int);
FILE *AbrirArchivo(char[], char[]);
int LeerYValidarEntero(int, int);
void MostrarTarifasMes(TARIFAS *, int);
void InternoQueMenosViajesHizo(FILE *);
void GenerarArchivo(FILE *, FILE *, TARIFAS *, int);

int main()
{
    FILE *fpViajes, *fpTarifas, *fpRecaudacion;
    TARIFAS *t = NULL;
    int mes, tam = 0;

    fpViajes = AbrirArchivo("viajes.dat", "rb");
    fpTarifas = AbrirArchivo("tarifas.dat", "rb");
    fpRecaudacion = AbrirArchivo("recaudacion.dat", "wb");

    printf("\nIngrese el mes: ");
    mes = LeerYValidarEntero(1, 12);

    t = CargaTarifas(fpTarifas, mes, &tam);
    MostrarTarifasMes(t, tam);

    printf("\nEl importe total de la empresa es %.2f", CalcularImporte(fpViajes, t, tam));
    InternoQueMenosViajesHizo(fpViajes);
    GenerarArchivo(fpRecaudacion, fpViajes, t, tam);
    MostrarViajes(fpViajes);

    free(t);
    fclose(fpViajes);
    fclose(fpTarifas);
    fclose(fpRecaudacion);

    return 0;
}

int LeerYValidarEntero(int linf, int lsup)
{
    int num;
    do
    {
        printf("\nIngrese el numero (%d-%d): ", linf, lsup);
        scanf("%d", &num);
    } while (num < linf || num > lsup);
    return num;
}

TARIFAS *CargaTarifas(FILE *fpTarifas, int mes, int *tam)
{
    TARIFAS *t = NULL, *auxT = NULL, indT;
    *tam = 0;
    rewind(fpTarifas);

    fread(&indT, sizeof(TARIFAS), 1, fpTarifas);
    while (!feof(fpTarifas))
    {
        if (indT.mes == mes)
        {
            auxT = (TARIFAS *)realloc(t, ((*tam) + 1) * sizeof(TARIFAS));
            if (auxT == NULL)
            {
                printf("\nError en la ejecucion");
                exit(1);
            }
            t = auxT;
            *(t + (*tam)) = indT;
            (*tam)++;
        }
        fread(&indT, sizeof(TARIFAS), 1, fpTarifas);
    }
    return t;
}

FILE *AbrirArchivo(char nom[], char mod[])
{
    FILE *fp = fopen(nom, mod);
    if (fp == NULL)
    {
        printf("\nError en la ejecucion");
        exit(1);
    }
    return fp;
}

float CalcularImporte(FILE *fpSube, TARIFAS *t, int tam)
{
    rewind(fpSube);
    float calculo = 0;
    SUBE s;
    int i;

    fread(&s, sizeof(SUBE), 1, fpSube);
    while (!feof(fpSube))
    {
        for (i = 0; i < tam; i++)
        {
            if (strcmp(s.cod, (t + i)->cod) == 0)
            {
                calculo += (t + i)->precio;
            }
        }
        fread(&s, sizeof(SUBE), 1, fpSube);
    }
    return calculo;
}

void MostrarTarifasMes(TARIFAS *t, int tam)
{
    int i;
    for (i = 0; i < tam; i++)
    {
        printf("\n %s %.2f", (t + i)->cod, (t + i)->precio);
    }
}

void GenerarArchivo(FILE *fpRecaudacion, FILE *fpViajes, TARIFAS *t, int tam)
{
    SUBE s, prevS;
    int i = 0;
    float costoT = 0;
    int cant = 0, hayDatos = 0;
    VIAJES_TARIFAS vt;

    rewind(fpViajes);
    fread(&s, sizeof(SUBE), 1, fpViajes);
    prevS = s;

    while (!feof(fpViajes))
    {
        hayDatos = 1;
        if (prevS.interno != s.interno)
        {
            vt.cant = cant;
            vt.costo = costoT;
            vt.interno = prevS.interno;
            fwrite(&vt, sizeof(VIAJES_TARIFAS), 1, fpRecaudacion);
            cant = 0;
            costoT = 0;
            prevS = s;
        }
        for (i = 0; i < tam; i++)
        {
            if (strcmp((t + i)->cod, s.cod) == 0)
            {
                cant++;
                costoT += ((t + i)->precio);
            }
        }
        fread(&s, sizeof(SUBE), 1, fpViajes);
    }

    if (hayDatos)
    {
        vt.cant = cant;
        vt.costo = costoT;
        vt.interno = prevS.interno;
        fwrite(&vt, sizeof(VIAJES_TARIFAS), 1, fpRecaudacion);
    }
    rewind(fpViajes);
}

void InternoQueMenosViajesHizo(FILE *fpViajes)
{
    int cant = 0, cantMenor = 0, band = 0, internoMenos = 0, hayDatos = 0;
    SUBE s, prevS;

    rewind(fpViajes);
    fread(&s, sizeof(SUBE), 1, fpViajes);
    prevS = s;

    while (!feof(fpViajes))
    {
        hayDatos = 1;
        if (prevS.interno != s.interno)
        {
            if (!band || (cant < cantMenor))
            {
                band = 1;
                cantMenor = cant;
                internoMenos = prevS.interno;
            }
            cant = 0;
            prevS = s;
        }
        cant++;
        fread(&s, sizeof(SUBE), 1, fpViajes);
    }

    if (hayDatos && (!band || (cant < cantMenor)))
    {
        band = 1;
        cantMenor = cant;
        internoMenos = prevS.interno;
    }

    rewind(fpViajes);
    if (band)
    {
        printf("\nEl interno que menos viajes hizo fue %d", internoMenos);
    }
}

int BuscarEnMemoria(VIAJES_TOT *vt, int tam, char cod[])
{
    int i = 0, idx = -1;
    while (i < tam && idx == -1)
    {
        if (strcmp((vt + i)->cod, cod) == 0)
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

void MostrarViajes(FILE *fpViajes)
{
    SUBE s, prevS;
    VIAJES_TOT *vt = NULL, *aux = NULL;
    int tam = 0, idx = 0, i;

    rewind(fpViajes);
    fread(&s, sizeof(SUBE), 1, fpViajes);
    prevS = s;

    while (!feof(fpViajes))
    {
        if (s.interno != prevS.interno)
        {
            printf("\nInterno del %d ", prevS.interno);
            OrdenarViajes(vt, tam);
            for (i = 0; i < tam; i++)
            {
                printf("\nViajes realizados %d con tarifa %s\n", (vt + i)->cant, (vt + i)->cod);
            }
            free(vt);
            vt = NULL;
            tam = 0;
            prevS = s;
        }

        idx = BuscarEnMemoria(vt, tam, s.cod);
        if (idx == -1)
        {
            aux = (VIAJES_TOT *)realloc(vt, (tam + 1) * sizeof(VIAJES_TOT));
            if (aux == NULL)
            {
                printf("\nERROR");
                exit(1);
            }
            vt = aux;
            (vt + tam)->cant = 1;
            strcpy((vt + tam)->cod, s.cod);
            (vt + tam)->interno = s.interno;
            tam++;
        }
        else
        {
            (vt + idx)->cant++;
        }

        fread(&s, sizeof(SUBE), 1, fpViajes);
    }

    if (tam > 0)
    {
        printf("\nInterno del %d ", prevS.interno);
        OrdenarViajes(vt, tam);
        for (i = 0; i < tam; i++)
        {
            printf("\nViajes realizados %d con tarifa %s\n", (vt + i)->cant, (vt + i)->cod);
        }
        free(vt);
    }
}

void OrdenarViajes(VIAJES_TOT *vt, int tam)
{
    int i, j;
    VIAJES_TOT aux;
    for (i = 0; i < tam - 1; i++)
    {
        for (j = 0; j < tam - i - 1; j++)
        {
            if ((vt + j)->cant < (vt + j + 1)->cant)
            {
                aux = *(vt + j);
                *(vt + j) = *(vt + j + 1);
                *(vt + j + 1) = aux;
            }
        }
    }
}