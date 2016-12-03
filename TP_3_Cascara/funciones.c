#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "ArrayList.h"

EMovie* pelicula_new(void)
{
    EMovie* returnAux = malloc(sizeof(EMovie));
    return returnAux;
}

int menu(char mensaje[],char error[])
{
    int op,aux;
    printf("%s",mensaje);
    aux=scanf("%d",&op);
    fflush(stdin);
    while(aux==0 ||(op<1||op>4))
    {
        printf("%s",error);
        fflush(stdin);
        aux=scanf("%d",&op);
    }
    return op;
}

void altaPelicula(EMovie *info,int cont)
{
    int aux,i;
    char nombre[50];
    char genero[50];
    char descripcion[250];
    if(info != NULL)
    {
        info->estado = 1;
        info->id = cont;
        printf("Ingrese nombre de la pelicula: ");
        fflush(stdin);
        gets(nombre);
        printf("Ingrese genero: ");
        fflush(stdin);
        gets(genero);
        printf("Ingrese descripcion: ");
        fflush(stdin);
        gets(descripcion);
        printf("Ingrese duracion: ");
        fflush(stdin);
        aux = scanf("%d",&info->duracion);
        while(aux == 0 || (info->duracion<40 || info->duracion>240))
        {
            printf("Ingrese la duracion nuevamente: ");
            fflush(stdin);
            aux = scanf("%d",&info->duracion);
        }
        printf("Ingrese puntaje del 1 al 5: ");
        fflush(stdin);
        aux = scanf("%d",&info->puntaje);
        while(aux==0 || (info->puntaje<1 || info->puntaje>5))
        {
            printf("Ingrese el puntaje nuevamente: ");
            fflush(stdin);
            aux=scanf("%d",&info->puntaje);
        }
        printf("Busque en internet la portada de la pelicula, copie el link de la imagen y pequelo aqui: ");
        fflush(stdin);
        gets(info->linkImagen);
        for(i=0;i<1;i++)
        {
           nombre[i] = toupper(nombre[i]);
           genero[i] = toupper(genero[i]);
           descripcion[i] = toupper(descripcion[i]);
        }
        strncpy(info->titulo,nombre,50);
        strncpy(info->genero,genero,50);
        strncpy(info->descripcion,descripcion,250);
    }

}

void Borrar(ArrayList *eliminarPelicula)
{
    EMovie *auxiliar;
    int i,flag=0,aux,id;
    printf("\nIngrese numero de id que desea eliminar: ");
    aux=scanf("%d",&id);
    while(aux==0)
    {
        printf("\nIngrese el id de la pelicula que desea eliminar: ");
        fflush(stdin);
        aux=scanf("%d",&id);
    }
    for(i=0;i<al_len(eliminarPelicula);i++)
    {
        auxiliar = al_get(eliminarPelicula,i);
        if(auxiliar->id == id)
        {
           auxiliar = al_pop(eliminarPelicula,al_indexOf(eliminarPelicula,auxiliar));
           printf("%d---%s---%s---%d---%d--%s",auxiliar->id,auxiliar->titulo,auxiliar->genero,auxiliar->duracion,auxiliar->puntaje,auxiliar->descripcion);
           flag=1;
           break;
        }
    }
    if(flag==1)
    {
        printf("\nSe borraron correctamente los datos\n\n");
    }
    else
    {
        printf("No existe pelicula con ese id\n");
    }
}

void mostrar(ArrayList *mostrarPelicula)
{
    EMovie *auxiliar;
    int i;
    if(mostrarPelicula != NULL)
    {
        for(i=0;i<al_len(mostrarPelicula);i++)
        {
            auxiliar = al_get(mostrarPelicula,i);
            printf("%d---%s---%s---%s---%d\n",auxiliar->id,auxiliar->titulo,auxiliar->genero,auxiliar->descripcion,auxiliar->duracion);
        }
    }
}

int Apertura(ArrayList *AperturaDeArchivo,FILE *pFile)
{
    EMovie *auxiliar;
    int id;
    pFile=fopen("peliculas.dat","rb");
    if(pFile!= NULL)
    {
        fread(&id, sizeof(int), 1, pFile);
        while(!feof(pFile))
        {
           auxiliar = pelicula_new();
           if(auxiliar != NULL)
           {
                if(fread(auxiliar,sizeof(EMovie),1,pFile) == 1)
                   al_add(AperturaDeArchivo,auxiliar);
           }
        }
    fclose(pFile);
    printf("Archivo levantado con exito\n\n");
    }
    else
    {
       printf("\n No existe el archivo %s.\n\n","peliculas.dat");
       id=1;
    }
    return id;
}

void Cerrar(ArrayList *CierreDeArchivo,FILE *pFile,int id)
{
    int cant,i;
    pFile = fopen("peliculas.dat","wb");
    if(pFile != NULL)
    {
        fwrite(&id,sizeof(int),1,pFile);
        cant = CierreDeArchivo->len(CierreDeArchivo);
        for(i=0;i<cant;i++)
        {
            fwrite((EMovie*)CierreDeArchivo->get(CierreDeArchivo,i),sizeof(EMovie),1,pFile);
        }
        fclose(pFile);
        printf("Archivo guardado con exito\n\n");
        system("pause");
    }
}

void GenerarPagina(ArrayList *Pag,EMovie *Peli)
{
    FILE *Pagina;
    EMovie *auxiliar;
    int i;
    Pagina = fopen("Pagina.html","w");
    if(Pagina != NULL)
    {
        for(i=0;i<al_len(Pag);i++)
        {
            auxiliar = al_get(Pag,i);
            fprintf(Pagina,"<article class='col-md-4 article-intro'><a href='#'><img class='img-responsive img-rounded' src='%s'alt=''>",auxiliar->linkImagen);
            fprintf(Pagina,"</a><h3><a href='#'>%s</a></h3><ul>",auxiliar->titulo);
            fprintf(Pagina,"<li>Género:%s</li>",auxiliar->genero);
            fprintf(Pagina,"<li>Puntaje:%d</li>",auxiliar->puntaje);
            fprintf(Pagina,"<li>Duracion:%d</li></ul>",auxiliar->duracion);
            fprintf(Pagina,"<p>Descripcion:%s</p></article>",auxiliar->descripcion);
        }
        fclose(Pagina);
        printf("Pagina creada con exito\n\n");
        system("pause");
    }
}

