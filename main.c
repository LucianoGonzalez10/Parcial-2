#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>

typedef struct
{
    int id;
    char nombreDisfraz[40];
    char genero[10];
    int precioAlquiler;
} Disfraz;

int cargarArreglo(Disfraz d[], int dimension);
void recorrerArreglo(Disfraz d[], int validos, int *cantHom, int *cantMuj);
void cargarArchivos(Disfraz d[], int validos);
void mostrarArchivo(Disfraz d[], int validos);

int main()
{
    Disfraz d[100];

    int validos = 0;
    validos = cargarArreglo(d, 100);

    int cantHom = 0, cantMuj = 0;

    recorrerArreglo(d, validos, &cantHom, &cantMuj);
    printf("Cantidad de disfraces de hombre con precio mayor al elegido : %i \n", cantHom);
    printf("Cantidad de disfraces de mujer con precio mayor al elegido : %i \n", cantMuj);

    cargarArchivos(d, validos);
    mostrarArchivo(d, validos);

    return 0;
}

int cargarArreglo(Disfraz d[], int dimension)
{
    char control = 's';
    int i = 0;
    int validos = 0;
    printf("Desea cargar disfraces:? (s/n) \n");
    fflush(stdin);
    scanf("%c", &control);

    while(i<dimension && (control == 's' || control == 'S'))
    {
        printf("Ingrese el ID del disfraz \n");
        scanf("%d", &d[i].id);

        printf("Ingrese el nombre del disfraz: \n");
        fflush(stdin);
        gets(d[i].nombreDisfraz);

        printf("Ingrese el genero del disfraz \n");
        fflush(stdin);
        gets(d[i].genero);

        while(strcmpi(d[i].genero, "hombre")!= 0 && strcmpi(d[i].genero, "mujer") != 0)
        {
            printf("Ingrese un genero valido \n");
            fflush(stdin);
            gets(d[i].genero);
        }

        printf("Ingrese el precio del alquiler del disfraz \n");
        scanf("%d", &d[i].precioAlquiler);

        printf("Desea seguir cargando disfraces:? \n");
        fflush(stdin);
        scanf("%c", &control);
        i++;
    }
    validos = i;
    return validos;
}

void recorrerArreglo(Disfraz d[], int validos, int *cantHom, int *cantMuj)
{
    int i = 0, precioElegido = 0;

    printf("Ingrese el precio a buscar: \n");
    scanf("%i", &precioElegido);

    while(i<validos)
    {
        if(strcmpi(d[i].genero, "hombre" == 0) && d[i].precioAlquiler >= precioElegido)
        {
            *cantHom = *cantHom + 1;
        }
        else if(strcmpi(d[i].genero, "mujer" == 0) && d[i].precioAlquiler >= precioElegido)
        {
            *cantMuj = *cantMuj + 1;
        }
        i++;
    }
}

void cargarArchivos(Disfraz d[], int validos)
{
    FILE *buffer = fopen("hombres.bin", "ab");
    FILE *buffer2 = fopen("mujeres.bin", "ab");
    int i = 0;
    if(buffer)
    {
        while(i<validos)
        {
            if(strcmpi(d[i].genero, "hombre")== 0)
            {
                fwrite(&d[i], sizeof("hombres.bin"), 1, buffer);
                i++;
            }

        }

    }

    if(buffer2)
    {
        while(i<validos)
        {
            if(strcmpi(d[i].genero, "mujer")== 0)
            {
                fwrite(&d[i], sizeof("mujeres.bin"), 1, buffer2);
                i++;
            }

        }
    }
    fclose(buffer);
    fclose(buffer2);
}

void mostrarArchivo(Disfraz d[], int validos)
{
    FILE *buffer = fopen("hombres.bin", "rb");
    FILE *buffer2 = fopen("mujeres.bin", "rb");
    int i = 0;
    while(i<validos)
    {
        while(fread(&d[i], sizeof("hombres.bin"),1, buffer) > 0)
        {
            printf("ID del disfraz %i \n",d[i].id);
            printf("Nombre del disfraz: %s \n",d[i].nombreDisfraz);
            printf("Genero: %s \n",d[i].genero);
            printf("Precio del alquiler del disfraz: %i \n",d[i].precioAlquiler);

        }

        while(fread(&d[i], sizeof("mujeres.bin"),1, buffer2) > 0)
        {
            printf("ID del disfraz %i \n",d[i].id);
            printf("Nombre del disfraz %s \n",d[i].nombreDisfraz);
            printf("Genero %s \n",d[i].genero);
            printf("Precio del alquiler del disfraz %i \n",d[i].precioAlquiler);
        }
        i++;
    }

}

