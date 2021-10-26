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
    unsigned long cPalabras;
    unsigned long cCaracter;
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

void traspasarLista(HashMap * documentos, HashMap * palabras){
    Documento * docu = firstMap(documentos);
    Palabra * pala = firstMap(docu->map);
    while(docu != NULL){
        while(pala != NULL){
            if(searchMap(palabras, pala->word) == NULL){
                Contador * new = (Contador *)malloc(sizeof(Contador));
                strcpy(new->palabrota, pala->word);
                new->mapa = createMap(100);
                insertMap(new->mapa, docu->nombre, docu->nombre);
                insertMap(palabras, new->palabrota, new);
            }else{
                Contador * cont = searchMap(palabras, pala->word);
                if(searchMap(cont->mapa, docu->nombre) != NULL){
                    pala = nextMap(docu->map);    
                }else{
                    insertMap(cont->mapa, docu->nombre, docu->nombre);
                }
            }
            pala = nextMap(docu->map);
        }
        docu = nextMap(documentos);
    }
}

void contarCaracteres(HashMap * documentos){
    Documento * new = firstMap(documentos);
    while(new != NULL){
        int cantP = 0;
        int cantC = 0;
        HashMap * docu = firstMap(new->map);
        Palabra * pala = firstMap(docu);
        while(pala != NULL){
            cantP = cantP + 1;
            cantC = cantC + strlen(pala->word);
            pala = nextMap(docu);
        }
        new->cPalabras = cantP;
        new->cCaracter = cantC;
        new = nextMap(documentos);
    }

    
}

void cargarDoc(HashMap * documentos, HashMap * palabras){
    char scan[200];
    int i = 0;
    printf(" Ingrese los nombres de los archivos a cargar: \n");
    gets(scan);
    FILE * archivo;
    char nombreArchivo[30];
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
                char guardar[30];
                strcpy(guardar, txt(linea, j));
                Documento * doc = searchMap(documentos, nombreArchivo);
                if(doc == NULL){
                    Documento * new = (Documento *)malloc(sizeof(Documento));
                    new->map = createMap(50);
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
                        Palabra * new = (Palabra *)malloc(sizeof(Palabra));
                        new->cant = 1;
                        strcpy(new->word, guardar);
                        insertMap(doc->map, new->word, new);
                    }
                }
            }
        }
        i++;
    }
    if(firstMap(documentos) != NULL){
        contarCaracteres(documentos);
        traspasarLista(documentos, palabras);
    }
    
}

void mostrarDoc(HashMap * documentos){
    Documento * new = firstMap(documentos);
    if(new == NULL){
        printf("No hay documentos\n");
        return;
    }
    while(new != NULL){
        printf("%s %lu palabras %lu caracteres\n", new->nombre, new->cPalabras, new->cCaracter);
        new = nextMap(documentos);
    }
}

void buscarPalabra(HashMap * documentos, HashMap * palabras){
    char buscada[30];
    printf("Ingrese la palabra a buscar\n");
    gets(buscada);
    Contador * cont = searchMap(palabras, buscada);
    if(cont == NULL){
        printf("No se encuentra la palabra\n");
        return;
    }
    char nombre[30];
    strcpy(nombre, nextMap(cont->mapa));
    while(nombre != NULL){
        Documento * new = searchMap(documentos, nombre);
        Palabra * pala = searchMap(new->map, buscada);
        printf("%s %i veces\n", nombre, pala->cant);
        strcpy(nombre, nextMap(cont->mapa));
    }
}



