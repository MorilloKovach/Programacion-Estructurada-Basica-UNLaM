#include <stdio.h>

typedef struct
{
    int codigo;
    char descripcion[31];
    float precio;
} sProductos;

int main()
{
    sProductos s, *a;
    printf("\nIngrese el codigo: ");
    scanf("%d",&s.codigo);
    printf("Ingrese la desc: ");
    scanf("%s",s.descripcion);
    printf("\nIngrese el precio: ");
    scanf("%f",&s.precio);

    a = &s;
    printf("\n%d %s %.2f\n", a->codigo, a->descripcion, a->precio);
    printf("\n %d %s %.2f\n", s.codigo, s.descripcion, s.precio);
}