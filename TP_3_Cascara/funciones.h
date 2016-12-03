#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"

typedef struct{
    char titulo[20];
    char genero[20];
    char descripcion[250];
    char linkImagen[250];
    int duracion;
    int puntaje;
    int estado;
    int id;
}EMovie;

int Apertura(ArrayList *AperturaDeArchivo,FILE *pFile);
void Cerrar(ArrayList *CierreDeArchivo,FILE *pFile,int id);
EMovie* pelicula_new(void);
int menu(char mensaje[],char error[]);
void mostrar(ArrayList *mostrarPelicula);
/**
 *  Agrega una pelicula
 *  @param Puntero a la estructura EMovie
 *  @param cont contador autoincremental
 */
void altaPelicula(EMovie *info,int cont);

/**
 *  Borra una pelicula del archivo binario
 *  @param Puntero al ArrayList
 */
void borrar(ArrayList *eliminarPelicula);

/**
 *  Genera un archivo html a partir de las peliculas cargadas en el archivo binario.
 *  @param Puntero al ArrayList
 *  @param Puntero a la estructura EMovie
 */
void GenerarPagina(ArrayList *Pag,EMovie *Peli);


