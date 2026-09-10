/*

EJERCICIO 5 UNIDAD 3

Se ingresan las ventas de un comercio de insumos de computación. Por cada venta se ingresa:
• Número de cliente (entero de 4 dígitos no correlativos).
• Importe (mayor a cero).
• Número de vendedor (entero de 1 a 10).
El ingreso de datos finaliza con un número de cliente 999.
Se sabe que no son más de 100 clientes, la carga de los clientes se debe realizar al inicio del programa con la
función CARGA_CLIENTE () y para cada uno se ingresa:
• Código de cliente (entero de 4 dígitos no correlativos).
• Nombre y Apellido (50 caracteres máximo).
Se solicita:
a. Determinar la cantidad de ventas realizadas por cliente.
b. La cantidad de ventas realizadas por vendedor.
c. Informar en forma ordenada por total facturado (modo descendente), el total facturado a cada
cliente, informando:
CODIGO DE CLIENTE NOMBRE Y APELLIDO TOTAL FACTURADO
X XXXXX XXXXXXXX $ XXXXXXXXX,XX

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int cod_cli;
    char *nombre_ap;
    int ventas_cliente;
    int *vendedor;
    float factura;

} CLIENTE;

int CARGA_CLIENTE(CLIENTE *, int);
int Busca(CLIENTE *, int, int);
int CargaRango(int, int);
char *Leer(int);
void CargarVentas(CLIENTE *, int);
void Ordenar(CLIENTE *, int);
void MostrarVentasClientes(CLIENTE *, int);
void VendidosVendedor(CLIENTE *, int);

int main()
{
    int i, tam, j;
    CLIENTE *clientes;
    clientes = calloc(100, sizeof(CLIENTE));
    if (clientes == NULL)
    {
        printf("\nError en la asignacion de memoria.");
        exit(1);
    }
    for (i = 0; i < 100; i++)
    {
        (clientes + i)->nombre_ap = calloc(50, sizeof(char));
        (clientes + i)->vendedor = calloc(10, sizeof(int));
        (clientes + i)->factura = 0;
        (clientes + i)->ventas_cliente = 0;
    }
    tam = CARGA_CLIENTE(clientes, 100);
    if (tam == 0)
    {
        printf("NO HUBO CARGA DE CLIENTES");
    }
    else
    {
        printf("\nINICIA LA CARGA DE LAS VENTAS\n");
        CargarVentas(clientes, tam);
        MostrarVentasClientes(clientes, tam);
        VendidosVendedor(clientes, tam);
        Ordenar(clientes, tam);
        printf("\nCODIGO DE CLIENTE\t NOMBRE Y APELLIDO \t TOTAL PAGADO");
        for (i = 0; i < tam; i++)
        {
            printf("\n%d\t%s\t%.2f\n", (clientes + i)->cod_cli, (clientes + i)->nombre_ap, (clientes + i)->factura);
        }
    }
    for (i = 0; i < 100; i++)
    {
        free((clientes + i)->nombre_ap);
        free((clientes + i)->vendedor);
    }
    free(clientes);
    return 0;
}

int Busca(CLIENTE *v, int tam, int cod)
{
    int i = 0, flag = -1;
    while (i < tam && flag == -1)
    {
        if ((v + i)->cod_cli == cod)
        {
            flag = i;
        }
        else
        {
            i++;
        }
    }
    return flag;
}

int CargaRango(int linf, int lsup)
{
    int num;
    scanf("%d", &num);
    while (!(linf <= num && num <= lsup))
    {
        printf("\nError, ingrese un numero en el rango: ");
        scanf("%d", &num);
    }
    return num;
}

char *Leer(int tam)
{
    char *ap;
    ap = calloc(50, sizeof(char));
    int i = 0;
    getchar();
    fgets(ap, 50, stdin);

    while (i < tam && ap[i] != '\0')
    {
        if (ap[i] == '\n')
        {
            ap[i] = '\0';
        }
        else
        {
            i++;
        }
    }
    return ap;
}

int CARGA_CLIENTE(CLIENTE *v, int tam)
{
    int i = 0, cod_cli;
    char *nom_ap;
    printf("\nIngrese el codigo del cliente: ");
    cod_cli = CargaRango(999, 9999);
    while (Busca(v, i, cod_cli) != -1)
    {
        printf("\nIngrese un codigo que no se encuentre: ");
        cod_cli = CargaRango(999, 9999);
    }
    while (i < tam && cod_cli != 999)
    {
        printf("\nIngrese el nombre y apellido del cliente: ");
        nom_ap = Leer(50);
        strcat((v + i)->nombre_ap, nom_ap);
        (v + i)->cod_cli = cod_cli;
        i++;
        printf("\nIngrese el codigo del cliente: ");
        cod_cli = CargaRango(999, 9999);
        while (Busca(v, i, cod_cli) != -1)
        {
            printf("\nIngrese un codigo que no se encuentre: ");
            cod_cli = CargaRango(999, 9999);
        }
        free(nom_ap);
    }
    return i;
}

void CargarVentas(CLIENTE *v, int tam)
{
    int cod_cli, idx;
    float importe;
    int num_vend;
    printf("\nIngrese el codigo del cliente: ");
    cod_cli = CargaRango(999, 9999);
    idx = Busca(v, tam, cod_cli);
    while (idx == -1 && cod_cli != 999)
    {
        printf("\nIngrese un codigo que exista: ");
        cod_cli = CargaRango(999, 9999);
        idx = Busca(v, tam, cod_cli);
    }
    while (cod_cli != 999)
    {
        printf("\nIngrese el importe: ");
        scanf("%f", &importe);
        while (importe <= 0)
        {
            printf("\nIngrese un importe valido: ");
            scanf("%f", &importe);
        }
        printf("\nIngrese el numero del vendedor: ");
        num_vend = CargaRango(1, 10);
        (v + idx)->factura += importe;
        (*((v + idx)->vendedor + num_vend - 1))++;
        (v + idx)->ventas_cliente++;
        printf("\nIngrese el codigo del cliente: ");
        cod_cli = CargaRango(999, 9999);
        idx = Busca(v, tam, cod_cli);
        while (idx == -1 && cod_cli != 999)
        {
            printf("\nIngrese un codigo que exista: ");
            cod_cli = CargaRango(999, 9999);
            idx = Busca(v, tam, cod_cli);
        }
    }
}

void Ordenar(CLIENTE *v, int tam)
{
    int i, j;
    CLIENTE aux;
    for (i = 0; i < tam - 1; i++)
    {
        for (j = 0; j < tam - i - 1; j++)
        {
            if ((v + j)->factura < (v + j + 1)->factura)
            {
                aux = *(v + j);
                *(v + j) = *(v + j + 1);
                *(v + j + 1) = aux;
            }
        }
    }
}

void MostrarVentasClientes(CLIENTE *v, int tam)
{
    int i = 0;
    for (i = 0; i < tam; i++)
    {
        printf("\nEl cliente %s vendio %d unidades.", (v + i)->nombre_ap, (v + i)->ventas_cliente);
    }
}

void VendidosVendedor(CLIENTE *v, int tam)
{
    int i, j, sum;
    for (i = 0; i < 10; i++)
    {
        sum = 0;
        for (j = 0; j < tam; j++)
        {
            sum += *((v + j)->vendedor + i);
        }
        printf("\nEl vendedor %d vendio %d unidades", i + 1, sum);
    }
}