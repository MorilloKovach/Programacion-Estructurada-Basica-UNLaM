#include <stdio.h>

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



int main()
{
    TARIFAS t;
    SUBE s;
    FILE *fp = fopen("tarifas.dat", "rb");
    FILE *fp2 = fopen("viajes.dat", "rb");
    fread(&s, sizeof(SUBE), 1, fp2);
    while (!feof(fp2))
    {
        printf("\n%s %d %d %d %d\n", s.cod, s.dia, s.hora, s.interno, s.tarjeta);
        fread(&s, sizeof(SUBE), 1, fp2);
    }

    fread(&t, sizeof(TARIFAS), 1, fp);
    while (!feof(fp))
    {
        printf("\n%d %s %.2f\n", t.mes, t.cod, t.precio);
        fread(&t, sizeof(TARIFAS), 1, fp);
    }
    fclose(fp);
    fclose(fp2);
    return 0;
}