#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"
#include "hashmap.h"
#include "documentos.h"

typedef struct Documento{
    char nombre[30];
    HashMap * map;
} Documento;

typedef struct Palabra{
    char word[30];
    int cant;    
} Palabra;

typedef struct Contador{
    char palabrota[30];
    HashMap * mapa;
} Contador;

char * txt (char * temp, int pos )
{
    char s[2] = " ";
    char * token = (char *) malloc (20 * sizeof(char));
    char * auxTemp = strdup(temp);
    int i = 0;

    token = strtok(auxTemp, s);
    while (token != NULL && i < pos)
    {
        token = strtok(NULL, s);
        i++;
    }
    return token;
}

void cargarDoc(HashMap * documentos, List * palabras){
    char scan[200];
    int i = 0;
    printf(" Ingrese los nombres de los archivos a cargar: \n");
    gets(scan);
    FILE * archivo;
    char * nombreArchivo;
    while(txt(scan,i) != NULL){
        strcpy(nombreArchivo, txt(scan, i));
        archivo = fopen(nombreArchivo,"r");
        if(archivo == NULL){
            printf(" El archivo no existe\n");
            return;
        }
        int j = 0;
        char *linea = (char*)malloc(1024*sizeof(char));
        while(fgets(linea, 1023, archivo) != NULL){
            while(txt(linea, j) != NULL){
                char * guardar;
                strcpy(guardar, txt(linea, j));
                Documento * doc = searchMap(documentos, nombreArchivo);
                if(doc == NULL){
                    Documento * new = (Documento *)malloc(sizeof(Documento));
                    strcpy(new->nombre, nombreArchivo);
                    Palabra * nueva = (Palabra *)malloc(sizeof(Palabra));
                    nueva->cant = 1;
                    strcpy(nueva->word, guardar);
                    insertMap(new->map, nueva->word, nueva);
                    insertMap(documentos, new->nombre, new);
                    j++;
                }else{
                    Palabra * busc = searchMap(doc->map, guardar);
                    if(busc != NULL){
                        busc->cant ++;
                        j++;
                    }else{
                     strcpy(busc->word, guardar);
                        busc->cant = 1;
                        j++;
                    }
                }
            }
        }
        i++;
        printf("opa\n");
    }
    
}



