#include <stdio.h>
#include <stdlib.h>

#define TAM 1
typedef struct
{
    int codigo; // 3 cifras
    float precio;
    int stock;

} MEDICAMENTOS;
void cargarDatos(MEDICAMENTOS *, int);
float BUSQUEDA_MEDI(MEDICAMENTOS *, int, int);
void informarCodigos(MEDICAMENTOS *, int);
int validarInferior(int);
float validarInferiorReal(int);
int validarRango(int, int);

int main()
{
    MEDICAMENTOS *med;
    float val;
    med = calloc(TAM, sizeof(MEDICAMENTOS));
    cargarDatos(med, TAM);
    val = BUSQUEDA_MEDI(med, TAM, 100);
    if (val == -1)
    {
        printf("\nNo existe ese codigo.");
    }
    else
    {
        printf("\n%.2f", val);
    }
    informarCodigos(med, TAM);
    return 0;
}
float validarInferiorReal(int linf)
{
    float v;
    scanf("%f", &v);
    while (v < linf)
    {
        printf("\nError. No es un valor perteneciente al rango. Ingrese otro: ");
        scanf("%f", &v);
    }
    return v;
}
int validarRango(int linf, int lsup)
{
    int v;
    scanf("%d", &v);
    while (!(linf <= v && v <= lsup))
    {
        printf("\nError. No esta en el rango. Ingrese otro: ");
        scanf("%d", &v);
    }
    return v;
}

int validarInferior(int linf)
{
    int v;
    scanf("%d", &v);
    while (v < linf)
    {
        printf("\nError. No respeta el rango. Ingrese otro valor: ");
        scanf("%d", &v);
    }
    return v;
}
void informarCodigos(MEDICAMENTOS *v, int tam)
{
    int i = 0;
    for (i = 0; i < tam; i++)
    {
        if ((v + i)->stock < 10)
        {
            printf("%d\n", (v + i)->codigo);
        }
    }
}

float BUSQUEDA_MEDI(MEDICAMENTOS *med, int tam, int cod)
{
    int i = 0;
    float flag = -1;
    while (i < tam && flag == -1)
    {

        if ((med + i)->codigo == cod)
        {
            flag = (med + i)->precio;
        }
        else
        {
            i++;
        }
    }
    return flag;
}

void cargarDatos(MEDICAMENTOS *v, int tam)
{
    int i, codigo, stock;
    float precio;
    for (i = 0; i < tam; i++)
    {
        printf("\nIngrese el codigo: ");
        codigo = validarRango(100, 999);

        printf("\nIngrese el precio de codigo: ");
        precio = validarInferiorReal(0);
        printf("\nIngrese el stock: ");
        stock = validarInferior(0);

        (v + i)->codigo = codigo;
        (v + i)->precio = precio;
        (v + i)->stock = stock;
    }
}