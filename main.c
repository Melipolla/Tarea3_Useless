#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "list.h"
#include "hashmap.h"
#include "documentos.h"

int main(){
    srand(time(NULL));
    HashMap * documentos = createMap(100);
    List * palabras = createList();

    int menu = 1;
     while(menu!= 0){
        printf("===============================================================\n");
        printf("|   1.- Cargar Documentos                                    |\n");
        printf("|   2.- Mostrar Documentos ordenados                         |\n");
        printf("|   3.- Buscar por Palabra                                   |\n");
        printf("|   4.- Palabras con mayor frecuencia                        |\n");
        printf("|   5.- Palabras mas relevantes                              |\n");
        printf("|   6.- Buscar palabra en documento                          |\n");
        printf("===============================================================\n");
        printf(" Ingrese un numero: ");
        scanf("%i", &menu);
        while(menu < 0 || menu > 6){
            printf (" Por favor ingrese uno de los numeros anteriores: ");
            while(getchar()!='\n'); //limpiar buffer del teclado en caso de que el usuario ingrese una opcion no valida
            scanf (" %d", &menu);
            if(menu == 0 ) exit(0); 
        }
        fflush(stdin);
        switch (menu){
        case 1:
           cargarDoc(documentos, palabras);          
        }
    }
    return 0;
}