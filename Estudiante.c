#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct estudiante{
    char nombreEstudiante[30];
    char apellidoEstudiante[30];
    int edad;
    struct estudiante *sig;
    struct materia *listaMaterias;
};

// "Crear y listar estudiantes"
void listarEstudiante(struct estudiante **primero, char nombreEstudiante[30], char apellidoEstudiante[30], int edad){
    struct estudiante *nuevoEstudiante = malloc(sizeof(struct estudiante));
    strcpy(nuevoEstudiante->nombreEstudiante, nombreEstudiante);
    strcpy(nuevoEstudiante->apellidoEstudiante, apellidoEstudiante);
    nuevoEstudiante->edad = edad;
    nuevoEstudiante->sig = NULL;
    nuevoEstudiante->listaMaterias = NULL;

    if((*primero) == NULL){
        *primero = nuevoEstudiante;
    }
    else{
        if(strcmp(nombreEstudiante,(*primero)->nombreEstudiante) < 0){
            nuevoEstudiante->sig = *primero;
            *primero = nuevoEstudiante;
        } else{
            struct estudiante *cursor = (*primero);

            while(cursor->sig != NULL && strcmp(nombreEstudiante,cursor->sig->nombreEstudiante) > 0) {
                cursor = cursor->sig;
            }
            nuevoEstudiante->sig = cursor->sig;
            cursor->sig = nuevoEstudiante;
        }
    }
}

// "Buscar estudiantes por nombre y apellido"
struct  estudiante *buscarPorNombreYApellido (struct estudiante *primero, char nombreEstudiante[30], char apellidoEstudiante[30]){
    struct estudiante *actual = primero;

    while(actual != NULL){
        //el strcmp "larga" 0 cuando lo encuentra, y 1 sino.
        if((strcmp(actual->nombreEstudiante,nombreEstudiante) == 0 ) &&
                (strcmp(actual->apellidoEstudiante, apellidoEstudiante)== 0)){
            printf("\nEstudiante encontrado: %s\n",actual->nombreEstudiante, actual->apellidoEstudiante);
            return actual;
        }
        actual = actual->sig;
    }
    printf("\nEl estudiante no se encontró\n");
    return NULL;
}
//funcion para buscar estudiantes por rango etario
struct estudiante *buscarPorRangoEtario(struct estudiante *lista, int edadMin, int edadMax){

    struct estudiante *cursor = lista;
    int detener = 0;
    int masDeUnEstudiante = 0;

    while(cursor != NULL && detener == 0){
        if(edadMin > edadMax){
            printf("La edad minima no puede ser mayor que la edad maxima");
            detener = 1;
        }
        if(edadMin <=0 || edadMax <=0){
            printf("\nIngrese una edad correcta");
            detener = 1;
        } else {

            if(cursor->edad >= edadMin && cursor->edad <= edadMax){
                if(masDeUnEstudiante == 0){
                    printf("\nEn el rango etario solicitado se encontraron los siguientes alumnos: \n\n");
                    masDeUnEstudiante = 1;
                }
                printf("%s %s, edad: %d", cursor->nombreEstudiante, cursor->apellidoEstudiante, cursor->edad);
                printf("\n");
            }
        }
        cursor = cursor->sig;
    }
    return NULL;
}

void imprimirListaEstudiantes(struct estudiante *lista){
    while(lista!= NULL){
        printf("%s %s \n", lista->nombreEstudiante, lista->apellidoEstudiante);
        lista = lista->sig;
    }
}

int cantidadDeEstudiantes(struct estudiante *lista) {
    int contador = 0;
    while(lista != NULL){
        contador++;
        lista= lista->sig;
    }
    return contador;
}

