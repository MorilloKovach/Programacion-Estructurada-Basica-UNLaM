/*
Se dispone de un archivo denominado INSCRIPTOS.dat que contiene la información de los inscriptos a un
curso de programación. El archivo aún no está completo ya que la inscripción se realiza por partes. Por
cada inscripto se tiene la siguiente información:
• DNI (entero)
• Apellido y Nombres (texto de 20 caracteres máximo)
• Pagado (campo entero donde 1 indica que pagó y 0 que aún adeuda la matrícula)
Se desea realizar un programa que cumpla con dos funciones:
a. Registrar los pagos de los alumnos ya inscriptos.
b. SI hay cupo, agregar nuevos inscriptos (el cupo máximo es de 60 alumno).
El programa solicitará el ingreso del DNI y lo buscará entre los inscriptos, en caso de que lo encuentre
dará la opción para registrar el pago (si es que no está pago ya). En caso de que no lo encuentre dará la
opción para inscribirlo al curso (el pago se realiza luego). En el momento que ya no quede cupo en el curso
si llega un nuevo inscripto se le preguntará si desea quedar registrado para un curso futuro, y en caso
afirmativo se le solicitará el teléfono y se guardará el nombre, DNI y teléfono en un archivo
Interesados.dat.
El ingreso de datos finaliza con un DNI negativo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 21

typedef struct
{
    int DNI;
    char ApNom[TAM];
    int pagado;
} INSCRIPTOS;

typedef struct
{
    char ApNom[TAM];
    int DNI;
    int telefono;
} INTERESADOS;

int LeerYValidarEntero(int, int);
int BuscarEnRegistros(FILE *, INSCRIPTOS *, int);
void LeerTexto(char[], int);
INTERESADOS CargarInteresado(int);
void NoEstaEnRegistro(FILE *, FILE *, int , INTERESADOS *, INSCRIPTOS *);
void SetearPago(INSCRIPTOS *, FILE *);
FILE *Abrir_archivo(char[], char[]);
void RomperAlFallar(void *);

int main()
{
    FILE *fpInscriptos = Abrir_archivo("INSCRIPTOS.dat", "r+b");
    FILE *fpInteresados = Abrir_archivo("INTERESADOS.dat", "w+b");
    INSCRIPTOS inscripto;
    INTERESADOS interesado;
    int dni;
    printf("\nInicio del programa. Arrancamos solicitando DNIS para ver si estan en los inscriptos.\n");
    printf("\nIngrese el DNI: ");
    scanf("%d", &dni);
    while (dni >= 0)
    {
        if (!BuscarEnRegistros(fpInscriptos, &inscripto, dni))
        {
            NoEstaEnRegistro(fpInscriptos, fpInteresados, dni, &interesado, &inscripto);
        }
        else
        {
            SetearPago(&inscripto, fpInscriptos);
        }
        printf("\nIngrese DNI: ");
        scanf("%d", &dni);
    }
    fclose(fpInscriptos);
    fclose(fpInteresados);
    return 0;
}

FILE *Abrir_archivo(char arch[], char mod[])
{
    FILE *fp = fopen(arch, mod);
    RomperAlFallar(fp);
    return fp;
}
void RomperAlFallar(void *ptr)
{
    if (ptr == NULL)
    {
        printf("\nERROR EN LA ASIGNACION");
        exit(1);
    }
}

void LeerTexto(char str[], int tam)
{
    int i = 0;
    fflush(stdin);
    while (getchar() != '\n')
        ;
    fgets(str, tam, stdin);
    while (i < tam && str[i] != '\0')
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
        }
        else
        {
            i++;
        }
    }
}
int LeerYValidarEntero(int linf, int lsup)
{
    int opc;
    do
    {
        printf("\nIngrese la opcion (%d-%d): ", linf, lsup);
        scanf("%d", &opc);
    } while (opc < linf || opc > lsup);
    return opc;
}

int BuscarEnRegistros(FILE *fp, INSCRIPTOS *p, int dni)
{
    int encontrado = 0;
    rewind(fp);
    fread(p, sizeof(INSCRIPTOS), 1, fp);
    while (!feof(fp) && !encontrado)
    {
        if (p->DNI == dni)
        {
            encontrado = 1;
        }
        else
        {
            fread(p, sizeof(INSCRIPTOS), 1, fp);
        }
    }
    return encontrado;
}

INTERESADOS CargarInteresado(int dni)
{
    INTERESADOS inte;
    inte.DNI = dni;
    printf("\nIngrese su nombre: ");
    LeerTexto(inte.ApNom, TAM);
    printf("\nIngrese el numero de telefono: ");
    inte.telefono = LeerYValidarEntero(10000000, 99999999); // de tipo XXXX-YYYY
    return inte;
}

void NoEstaEnRegistro(FILE *fpInscriptos, FILE *fpInteresados, int dni, INTERESADOS *interesado, INSCRIPTOS *inscripto)
{
    char ApNom[TAM];
    int opc;
    if (ftell(fpInscriptos) / sizeof(INSCRIPTOS) == 60)
    {
        printf("\nNo hay mas cupos. Desea ingresar a la lista de espera en futuros cursos? (1 si, 2 no): ");
        opc = LeerYValidarEntero(1, 2);
        if (opc == 1)
        {
            *interesado = CargarInteresado(dni);
            fwrite(interesado, sizeof(INTERESADOS), 1, fpInteresados);
        }
        else
        {
            printf("\nOk\n");
        }
    }
    else
    {
        printf("\nIngrese su nombre.");
        LeerTexto(ApNom, TAM);
        fflush(fpInscriptos);
        printf("\nAnotado de forma exitosa.");
        inscripto->DNI = dni;
        strcpy(inscripto->ApNom, ApNom);
        inscripto->pagado = 0;
        fwrite(inscripto, sizeof(INSCRIPTOS), 1, fpInscriptos);
    }
}

void SetearPago(INSCRIPTOS *inscripto, FILE *fpInscriptos)
{
    int opc;
    if (inscripto->pagado == 0)
    {
        printf("\nDesea pagar? (1 si 2 no): ");
        opc = LeerYValidarEntero(1, 2);
        if (opc == 1)
        {
            inscripto->pagado = 1;
            fseek(fpInscriptos, (long)sizeof(INSCRIPTOS) * -1, SEEK_CUR);
            fwrite(inscripto, sizeof(INSCRIPTOS), 1, fpInscriptos);
            printf("\nPago realizado con exito. \n");
        }
        else
        {
            printf("\nOk.\n");
        }
    }
}