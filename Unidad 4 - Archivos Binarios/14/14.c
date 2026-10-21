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
void RomperAlFallo(void *);
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
        printf("\nIngrese el numero: ");
        scanf("%d", &num);
    } while (num < linf || num > lsup);
    return num;
}

int BuscarEnMemoria(VIAJES_TOT *vt, int tam, char cod[])
{
    int i = 0, pos = -1;
    while (i < tam && pos == -1)
    {
        if (strcmp((vt + i)->cod, cod) == 0)
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

void RomperAlFallo(void *ptr)
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
    RomperAlFallo(fp);
    return fp;
}

TARIFAS *CargaTarifas(FILE *fpTarifas, int mes, int *tam)
{
    TARIFAS *t, *aux, tarifa;
    t = NULL;
    fread(&tarifa, sizeof(TARIFAS), 1, fpTarifas);
    while (!feof(fpTarifas))
    {
        if (tarifa.mes == mes)
        {
            aux = (TARIFAS *)realloc(t, ((*tam) + 1) * sizeof(TARIFAS));
            RomperAlFallo(aux);
            t = aux;
            *(t + (*tam)) = tarifa;
            (*tam)++;
        }
        fread(&tarifa, sizeof(TARIFAS), 1, fpTarifas);
    }
    rewind(fpTarifas);
    return t;
}

void MostrarTarifasMes(TARIFAS *t, int tam)
{
    int i;
    printf("\nCODIGO \t PRECIO");
    for (i = 0; i < tam; i++)
    {
        printf("\n%s %.2f", (t + i)->cod, (t + i)->precio);
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
            if ((vt + j)->cant < ((vt + j + 1)->cant))
            {
                aux = *(vt + j);
                *(vt + j) = *(vt + j + 1);
                *(vt + j + 1) = aux;
            }
        }
    }
}

float CalcularImporte(FILE *fpSube, TARIFAS *t, int tam)
{
    float total = 0;
    SUBE s;
    int i = 0;
    fread(&s, sizeof(SUBE), 1, fpSube);
    while (!feof(fpSube))
    {
        for (i = 0; i < tam; i++)
        {
            if (strcmp((t + i)->cod, s.cod) == 0)
            {
                total += (t + i)->precio;
            }
        }
        fread(&s, sizeof(SUBE), 1, fpSube);
    }
    rewind(fpSube);
    return total;
}

void InternoQueMenosViajesHizo(FILE *fpViajes)
{
    int cant = 0, cantMenor = 0, band = 0, internoMenos = 0, internoAnterior;
    SUBE s;
    fread(&s, sizeof(SUBE), 1, fpViajes);
    internoAnterior = s.interno;
    while (!feof(fpViajes))
    {
        if (s.interno != internoAnterior)
        {
            if (!band || (cant < cantMenor))
            {
                band = 1;
                cantMenor = cant;
                internoMenos = internoAnterior;
            }
            cant = 0;
            internoAnterior = s.interno;
        }
        cant++;
        fread(&s, sizeof(SUBE), 1, fpViajes);
    }
    if (!band || (cant < cantMenor))
    {
        cantMenor = cant;
        internoMenos = internoAnterior;
    }
    printf("\nEl interno que menos viajes hizo fue %d", internoMenos);
    rewind(fpViajes);
}

void GenerarArchivo(FILE *fpRecaudacion, FILE *fpViajes, TARIFAS *t, int tam)
{
    int i = 0;
    float recaudacion = 0;
    int cant = 0;
    int interno = 0;
    SUBE s;
    VIAJES_TARIFAS vt;
    fread(&s, sizeof(SUBE), 1, fpViajes);
    interno = s.interno;
    while (!feof(fpViajes))
    {
        if (interno != s.interno)
        {
            vt.cant = cant;
            vt.costo = recaudacion;
            vt.interno = interno;
            cant = 0;
            recaudacion = 0;
            interno = s.interno;
            fwrite(&vt, sizeof(VIAJES_TARIFAS), 1, fpRecaudacion);
        }
        for (i = 0; i < tam; i++)
        {
            if (strcmp(s.cod, (t + i)->cod) == 0)
            {
                cant++;
                recaudacion += (t + i)->precio;
            }
        }
        fread(&s, sizeof(SUBE), 1, fpViajes);
    }
    vt.cant = cant;
    vt.costo = recaudacion;
    vt.interno = interno;
    fwrite(&vt, sizeof(VIAJES_TARIFAS), 1, fpRecaudacion);
    rewind(fpViajes);
}

void MostrarViajes(FILE *fpViajes)
{
    SUBE s;
    VIAJES_TOT *vt, *aux;
    int idx, tam = 0;
    int interno;
    fread(&s, sizeof(SUBE), 1, fpViajes);
    interno = s.interno;
    vt = NULL;
    while (!feof(fpViajes))
    {
        if (interno != s.interno)
        {
            OrdenarViajes(vt, tam);
            for (idx = 0; idx < tam; idx++)
            {
                printf("\n%s %d %d", (vt + idx)->cod, (vt + idx)->cant, (vt + idx)->interno);
            }
            free(vt);
            vt = NULL;
            tam = 0;
            interno = s.interno;
        }
        idx = BuscarEnMemoria(vt, tam, s.cod);
        if (idx == -1)
        {
            aux = (VIAJES_TOT *)realloc(vt, (tam + 1) * sizeof(VIAJES_TOT));
            RomperAlFallo(aux);
            vt = aux;
            (vt + tam)->cant = 1;
            strcpy((vt + tam)->cod, s.cod);
            (vt + tam)->interno = interno;
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
        OrdenarViajes(vt, tam);
        for (idx = 0; idx < tam; idx++)
        {
            printf("\n%s %d %d", (vt + idx)->cod, (vt + idx)->cant, (vt + idx)->interno);
        }
        free(vt);
    }
}