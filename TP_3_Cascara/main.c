#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"
#include "funciones.h"

int main()
{
    ArrayList *Peliculas = al_newArrayList();
    FILE *pFile = NULL;
    char seguir='s';
    int opcion,cont,aux;

    EMovie *datos;

    cont=Apertura(Peliculas,pFile);
    system("pause");

    while(seguir=='s')
    {
        system("cls");
        printf("Peliculas ingresadas: %d - Espacio disponible: %d\n",Peliculas->size,Peliculas->reservedSize);
        opcion = menu("1- Agregar pelicula\n2- Borrar pelicula\n3- Generar pagina web\n4- Salir\n","Error ingrese nuevamente una opcion entre 1 y 4: ");

        switch(opcion)
        {
        case 1:
            datos = pelicula_new();
            altaPelicula(datos,cont);
            aux = al_add(Peliculas,datos);
            if(aux == 0)
            {
                printf("\nSe cargaron correctamente los datos\n\n");
                cont++;
            }
            system("pause");
            break;
        case 2:
            mostrar(Peliculas);
            Borrar(Peliculas);
            system("pause");
            break;
        case 3:
            GenerarPagina(Peliculas,datos);
            break;
        case 4:
            Cerrar(Peliculas,pFile,cont);
            seguir = 'n';
            break;
        }
    }
    return 0;
}
