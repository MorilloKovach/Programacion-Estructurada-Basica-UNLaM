#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    float importeTot;
    int TotalVentas;
} Importes;

typedef struct
{
    int mes;
    int anio;
    int dia;
    int codprod;
    float importe;
} ventas;

void ValidarRango(int*, int*);
void VisualizarPorRango(Importes[10][12], int, int);
float VisualizarImporteMes(Importes[10][12], int);
float VisualizarImporteAnio(Importes[10][12], int);
void CargarMenu(Importes[10][12]);
int LeerYValidarMes();
int LeerYValidarAnio();
int LeerYValidarOpc();

int main()
{
    ventas auxVta;
    Importes imp[10][12];
    FILE *fp = fopen("ventas.dat","rb");
    if(fp == NULL)
    {
        printf("\nNO SE PUEDE ABRIR EL ARCHIVO");
        exit(1);
    }
    int anio1, anio2, i, j;
    for(i=0;i<10;i++)
    {
        for(j=0;j<12;j++)
        {
            imp[i][j].importeTot = 0;
            imp[i][j].TotalVentas = 0;
        }
    }
    fread(&auxVta, sizeof(ventas), 1, fp);
    while(!feof(fp))
    {
        printf("\n%f",auxVta.importe);
        imp[auxVta.anio-2014][auxVta.mes-1].importeTot += auxVta.importe;
        imp[auxVta.anio-2014][auxVta.mes-1].TotalVentas++;
        fread(&auxVta, sizeof(ventas),1,fp);
    }
    fclose(fp);
    anio1 = LeerYValidarAnio();
    anio2 = LeerYValidarAnio();
    ValidarRango(&anio1,&anio2);
    VisualizarPorRango(imp, anio1, anio2);
    CargarMenu(imp);
    return 0;
}
int LeerYValidarOpc()
{
    int opc;
    do{
        printf("\nIngrese opcion. 0 para terminar, 1 para ver el importe del anio, 2 para ver el importe del mes en total: ");
        scanf("%d",&opc);
    }while(opc < 0 || opc > 2);
    return opc;
}
int LeerYValidarMes()
{
    int mes;
    do
    {
        printf("\nIngrese el mes: ");
        scanf("%d", &mes);
    } while (mes < 1 || mes > 12);
    return mes;
}
void ValidarRango(int* anio1, int* anio2)
{
    int aux;
    if(*anio2 < *anio1)
    {
        aux = *anio2;
        *anio2 = *anio1;
        *anio1 = aux;
    }
}
int LeerYValidarAnio()
{
    int anio;
    do
    {
        printf("\nIngrese el anio: ");
        scanf("%d", &anio);
    } while (anio < 2014 || anio > 2023);
    return anio;
}
void VisualizarPorRango(Importes imp[10][12], int anioX, int anioY)
{
    int i = 0, j = 0;
    printf("\nMes 1\tMes2\tMes3\tMes4\tMes5\tMes6\tMes7\tMes8\tMes9\tMes10\tMes11\tMes12");
    for (i = anioX - 2014; i <= anioY - 2014; i++)
    {
        printf("\n%d ", i + 2014);
        for (j = 0; j < 12; j++)
        {
            printf(" %d ", imp[i][j].TotalVentas);
        }
        printf("\n");
    }
}

void CargarMenu(Importes imp[10][12])
{
    int opc, mes, anio;
    opc = LeerYValidarOpc();
    while(opc != 0)
    {
        if(opc==1)
        {
            anio = LeerYValidarAnio();
            printf("\nEl importe del anio es %.2f",VisualizarImporteAnio(imp, anio));
        }
        else
        {
            if(opc==2)
            {
                mes = LeerYValidarMes();
                printf("\nEl importe del mes a lo largo de los anios es %.2f", VisualizarImporteMes(imp, mes));
            }
        }
        opc = LeerYValidarOpc();
    }
}

float VisualizarImporteMes(Importes imp[10][12], int mes)
{
    int i = 0;
    float acum = 0;
    for(i=0;i<10;i++)
    {
        acum+=imp[i][mes-1].importeTot;
    }
    return acum;
}

float VisualizarImporteAnio(Importes imp[10][12], int anio)
{
    int i = 0;
    float acum = 0;
    for(i=0;i<12;i++)
    {
        acum+=imp[anio-2014][i].importeTot;
    }
    return acum;
}