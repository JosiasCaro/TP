#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Estudiante.c"

typedef struct Materia{
    char nombreMateria[30];
    int notaMateria;
    char estadoMateria[30];
    struct Materia *sig;
    struct Materia *materiasCorrelativas;
} Materia;

// "Crear y listar materias"
void listarMateria(Materia **primera, char nombreMateria[30]){
    Materia *nuevaMateria = malloc(sizeof(Materia));
    strcpy(nuevaMateria->nombreMateria, nombreMateria);
    strcpy(nuevaMateria->estadoMateria, "Cursando");
    nuevaMateria->notaMateria = 0;
    nuevaMateria->sig = NULL;
    nuevaMateria->materiasCorrelativas = NULL;
    if((*primera) == NULL){
        *primera = nuevaMateria;
    }
    else{
        Materia *cursor = (*primera);

        while(cursor->sig != NULL) {
            cursor = cursor->sig;
        }
        cursor->sig = nuevaMateria;
    }
}

Materia *buscarMateria(Materia *lista, char nombreMateria[30]){
    while (lista != NULL){
        if(strcmp(lista->nombreMateria, nombreMateria) == 0){
            return lista;
        }
        else{
            lista = lista->sig;
        }
    }
    return NULL;
}

void rendirMateria(Estudiante *estudiante, char nombreEstudiante[30], char apellidoEstudiante[30] ,char nombreMateria[30], int nota){
    Materia *actualMat = buscarMateria(estudiante->listaMaterias, nombreMateria);
    if(strcmp(actualMat->estadoMateria,"Aprobado") == 0) {
        printf("La materia ya esta aprobada, no se puede volver a rendir\n");
    }else{
        if(nota >= 4 && nota <= 10){
            actualMat->notaMateria = nota;
            strcpy(actualMat->estadoMateria, "Aprobado");
        }

        else if(nota > 10 || nota < 0){
            int notaNueva;
            printf("Nota invalida\nIngrese la nota correcta\n");
            scanf("%d",&notaNueva);
            rendirMateria(estudiante, nombreEstudiante, apellidoEstudiante, nombreMateria, notaNueva);
        }
        else{
            actualMat->notaMateria = nota;
            strcpy(actualMat->estadoMateria, "Desaprobado");
        }
    }
}


void agregarMateriaCorrelativa(Materia *listaDeMateriasExistentes, Materia *materia) {
    Materia *materiaBuscada = listaDeMateriasExistentes;
    while(materiaBuscada != NULL) { 
        if(strcmp(materia->nombreMateria, materiaBuscada->nombreMateria) == 0) {
            char nombreDeMateria[30];
            printf("Ingrese la materia que sera necesaria tener aprobada para anotarse a %s\n", materia->nombreMateria);
            scanf("%s",&nombreDeMateria);
            Materia *materiaCorrelativa = buscarMateria(listaDeMateriasExistentes, nombreDeMateria);
            Materia *materiaAux = malloc(sizeof(Materia));
            strcpy(materiaAux->nombreMateria, materiaCorrelativa->nombreMateria);
            if(materiaCorrelativa != NULL) {
                if(materiaBuscada->materiasCorrelativas == NULL) {
                    materiaBuscada->materiasCorrelativas = materiaAux;
                }
                else{
                    Materia *cursor = materiaBuscada->materiasCorrelativas;
                    while(cursor->sig != NULL) {
                        cursor = cursor->sig;
                    }
                    cursor->sig = materiaAux;
                }
            } else {
                printf("La materia %s no esta en la lista de materias exitentes", nombreDeMateria);
                break;
            }
        }
        materiaBuscada = materiaBuscada->sig;
    }
}

int verificarQueNoSeRepitaLaMateria(Materia* materia, Materia* nodo) {
    if(strcmp(nodo->nombreMateria, materia->nombreMateria) == 0 ) {
                printf("No es posible anotarse a %s mas de una vez\n", nodo->nombreMateria);
                return 0;
            }
    return 1;
}

int verificarQueTengaLasCorrelativasAprobadas(Estudiante *estudiante, Materia *materia) {
     // Obtener la materia a la que se desea anotar al estudiante
    Materia *materiaActual = materia->materiasCorrelativas;
    
    while (materiaActual != NULL) {
        // Verificar si la materia correlativa está presente en la listaMaterias del estudiante
        Materia *materiaEstudiante = estudiante->listaMaterias;
        int materiaEncontrada = 0;
        
        while (materiaEstudiante != NULL) {
            if (strcmp(materiaActual->nombreMateria, materiaEstudiante->nombreMateria) == 0) {
                materiaEncontrada = 1;
                break;
            }
            
            materiaEstudiante = materiaEstudiante->sig;
        }
        
        if (materiaEncontrada) {
            // Verificar si el estado de la materia en la listaMaterias del estudiante es "Aprobado"
            if (strcmp(materiaEstudiante->estadoMateria, "Aprobado") != 0) {
                return 0; // No se pueden anotar al estudiante si alguna materia correlativa no está aprobada
            }
        } else {
            return 0; // No se pueden anotar al estudiante si falta alguna materia correlativa en la listaMaterias
        }
        
        materiaActual = materiaActual->sig;
    }
    
    return 1; // Todas las materias correlativas están aprobadas en la listaMaterias del estudiante
}

void asignarMateria(Estudiante *estudiante, char nombreMateria[30]){
    Materia *materia = malloc(sizeof(Materia));
    strcpy(materia->nombreMateria, nombreMateria);
    strcpy(materia->estadoMateria, "Cursando");
    materia->notaMateria = 0;
    materia->sig = NULL;

    if (estudiante->listaMaterias == NULL) {
        estudiante->listaMaterias = materia;
        printf("\n%s es la primera materia de %s %s, por lo que no tiene correlativa\n", materia->nombreMateria, estudiante->nombreEstudiante, estudiante->apellidoEstudiante);
    }else{
        Materia *nodo = estudiante->listaMaterias;
        int error = verificarQueNoSeRepitaLaMateria(materia, nodo);
        if(error != 0) {
            while(error != 0 && nodo->sig != NULL) {
                error = verificarQueNoSeRepitaLaMateria(materia, nodo);
                nodo = nodo->sig;
            }
            nodo->sig = materia;
        }
    }
}

void calcularPromedio (Estudiante **lista, char nombreEstudiante[30], char apellidoEstudiante[30]){
    Estudiante *actualEst = buscarPorNombreYApellido(*lista, nombreEstudiante, apellidoEstudiante);
    Materia *listaMaterias = actualEst->listaMaterias;
    int cantidadMaterias = 0;
    int notas = 0;
    while(listaMaterias != NULL){
        if(strcmp(listaMaterias->estadoMateria,"Cursando") != 0){
            cantidadMaterias += 1;
            notas += listaMaterias->notaMateria;
        }
        listaMaterias = listaMaterias->sig;
    }
    printf("Promedio del estudiante: %.2f\n",(float)notas/(float)cantidadMaterias);
}

void calcularEstadisticaDeAlumnosEnUnaMateria(Materia* listaDeMaterias,Estudiante *ListaDeEstudiantes) {
    Materia *materia = listaDeMaterias;
    while(materia != NULL) {
        int contadorDeAnotados = 0;
        int contadorDeAprobados = 0;
        Estudiante *estudiante = ListaDeEstudiantes;
        while(estudiante != NULL) { 
            Materia *materiaDelAlumno = buscarMateria(estudiante->listaMaterias, materia->nombreMateria);
            if(materiaDelAlumno != NULL) {
                contadorDeAnotados++;
                if(strcmp(materiaDelAlumno->estadoMateria, "Aprobado") == 0) {
                    contadorDeAprobados++;
                }
            }
            estudiante = estudiante->sig;
        }
        printf("------%s------\n", materia->nombreMateria);
        printf("La materia %s hay %d alumnos anotados\n", materia->nombreMateria, contadorDeAnotados);
        printf("La materia %s hay %d alumnos aprobados\n", materia->nombreMateria, contadorDeAprobados);
        materia = materia->sig;
    }
}
