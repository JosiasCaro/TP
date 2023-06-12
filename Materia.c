#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Estudiante.c"

typedef struct Materia{
    char nombreMateria[30];
    char nombreMateriaCorrelativa[30];
    int notaMateria;
    char estadoMateria[30];
    struct Materia *sig;
} Materia;

// as = asignar materia
void asignarMateria(Estudiante *primero, char nombreMateria[30], char nombreMateriaCorrelativa[30]){

    struct Materia *as = malloc(sizeof(Materia));
    strcpy(as->nombreMateria, nombreMateria);
    strcpy(as->nombreMateriaCorrelativa, nombreMateriaCorrelativa);
    strcpy(as->estadoMateria, "Cursando");
    as->notaMateria=0;
    as->sig = NULL;
    if (primero->listaMaterias == NULL){
        strcpy(as->nombreMateriaCorrelativa, "No tiene");
        primero->listaMaterias = as;

        printf("\n%s es la primera materia de %s %s, por lo que no tiene correlativa\n", as->nombreMateria, primero->nombreEstudiante, primero->apellidoEstudiante);
    }
    else{
        Materia *nodo = primero->listaMaterias;
        int encontrado = 0;
        while(nodo != NULL && encontrado == 0){
            if(strcmp(nodo->nombreMateria, nombreMateriaCorrelativa) == 0){
                encontrado = 1;

                if(strcmp(nodo->estadoMateria, "Aprobado") == 0){
                    while (nodo->sig != NULL){
                        nodo = nodo->sig;
                    }
                    nodo->sig = as;
                } else{
                    printf("Materia correlativa no aprobada aun\n");
                }
            }
            nodo = nodo->sig;
        }

        if(encontrado == 0){

            printf("La materia correlativa %s no existe, se va a asumir que %s\nno tiene materia correlativa\n", as->nombreMateriaCorrelativa, as->nombreMateria);
            strcpy(as->nombreMateriaCorrelativa, "No tiene");

            Materia *nodo2 = primero->listaMaterias;
            while(nodo2->sig != NULL){
                nodo2 = nodo2->sig;
            }
            nodo2->sig = as;
        }

        Materia *nodo2 = primero->listaMaterias;

    }
}

// "Crear y listar materias"
void listarMateria(Materia **primera, char nombreMateria[30]){
    Materia *nuevaMateria = malloc(sizeof(Materia));
    strcpy(nuevaMateria->nombreMateria, nombreMateria);
    nuevaMateria->sig = NULL;

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
        if(strcmp(lista->nombreMateria,nombreMateria) == 0){
            return lista;
        }
        else{
            lista = lista->sig;
        }
    }
    return NULL;
}

void rendirMateria(Estudiante **lista, char nombreEstudiante[30], char apellidoEstudiante[30] ,char nombreMateria[30], int nota){
    Estudiante *actualEst = buscarPorNombreYApellido(*lista, nombreEstudiante, apellidoEstudiante);
    Materia *actualMat = buscarMateria(actualEst->listaMaterias, nombreMateria);

    if(nota >= 4 && nota <= 10){
        actualMat->notaMateria = nota;
        strcpy(actualMat->estadoMateria, "Aprobado");
    }

    else if(nota > 10 || nota < 0){
        int notaNueva;
        printf("Nota invalida\nIngrese la nota correcta\n");
        scanf("%d",&notaNueva);
        rendirMateria(lista, nombreEstudiante, apellidoEstudiante, nombreMateria, notaNueva);
    }
    else{
        actualMat->notaMateria = nota;
        strcpy(actualMat->estadoMateria, "Desaprobado");
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

//Imprime la informacion del estudiante y las materias asociadas al mismo
Estudiante *infoEstudiante(Estudiante *primero, char nombreEstudiante[30],char apellidoEstudiante[30]){
    Estudiante *actual = primero;
    while(actual != NULL){
        if((strcmp(actual->nombreEstudiante,nombreEstudiante) == 0 )&& (strcmp(actual->apellidoEstudiante,apellidoEstudiante) == 0)){
            //printf("Materia encontrada:%s\n",actual->lista_materias->nombreDeLaMateria);
            Materia *nodo = actual->listaMaterias;
            printf("\nMaterias de %s:\n\n", actual->nombreEstudiante);
            while(nodo != NULL){
                printf("Materia: %s, correlativa: %s, estado: %s, nota: %d\n", nodo->nombreMateria, nodo->nombreMateriaCorrelativa, nodo->estadoMateria, nodo->notaMateria);
                nodo = nodo->sig;
            }
            return actual;
        }
        actual = actual->sig;
    }
    return (NULL);
}


void imprimirListaMaterias(Materia *lista){
    while(lista!=NULL){
        printf("%s\n", lista->nombreMateria);
        lista = lista->sig;
    }
}

void imprimirDatos(Estudiante *actual, int i, int b){

    printf("[%d] Nombre del alumno:%s %s    Edad del alumno: %d\n",i, actual->nombreEstudiante, actual->apellidoEstudiante, actual->edad);
    Materia *materiaActual = actual->listaMaterias;
    while(materiaActual != NULL){
        printf("-----------------------------------------------\n");
        printf("[%d] \n",b);
        printf("Nombre del estudiante: %s\n",actual->nombreEstudiante);
        printf("Apellido del estudiante: %s\n",actual->apellidoEstudiante);
        printf("Edad del alumno: %d\n",actual->edad);

        printf("Nombre de la materia: %s\n",materiaActual->nombreMateria);
        printf("Nombre de la materia correlativa: %s\n",materiaActual->nombreMateriaCorrelativa);
        printf("Estado de la materia: %s\n",materiaActual->estadoMateria);
        printf("Nota de la materia: %d\n",materiaActual->notaMateria);
        printf("-----------------------------------------------\n");
        materiaActual = materiaActual->sig;
    }
}

void imprimirLista(Estudiante *lista){
    int i=1,b=1;
    Estudiante *actual;
    actual = lista;

    int cantidad = cantidadDeEstudiantes(lista);

    if(cantidad > 5){
        int contadorActual = 0;
        int contadorF = 0;
        int vuelve = 0;

        while(actual != NULL && vuelve == 0){
            if(contadorActual < 5){
                imprimirDatos(actual, i, b);
                contadorActual += 1;
                contadorF += 1;
                actual = actual ->sig;
                i += 1;
                b += 1;
            }
            if(contadorF == cantidad){
                char respuesta[1];
                printf("\nSe han mostrado todos los estudiantes, por favor presione la tecla numero 1 para volver al menu...\n");
                scanf("%s", respuesta);
                if(strcmp(respuesta,"1") == 0){
                    vuelve = 1;
                }
            }else if(contadorActual == 5 && actual->sig != NULL){
                contadorActual = 0;
                char respuesta[1];
                printf("\nPresione la tecla numero 6 para ir a la pagina siguiente o la tecla numero 1 para volver al menu...\n");
                scanf("%s", respuesta);
                if(strcmp(respuesta,"1") == 0){
                    vuelve = 1;
                }
            }
        }
    }else{
        while(actual != NULL){
            imprimirDatos(actual, i, b);
            b++;
            i++;
            actual = actual->sig;
        }
    }
}


Estudiante *veinteEstudiantesTest(Estudiante* lista){
    Estudiante *lista20 = lista;
    listarEstudiante( &lista20, "Estudiante1", "Apellido1", 18);
    listarEstudiante( &lista20, "Estudiante2", "Apellido2", 19);
    listarEstudiante( &lista20, "Estudiante3", "Apellido3", 20);
    listarEstudiante( &lista20, "Estudiante4", "Apellido4", 21);
    listarEstudiante( &lista20, "Estudiante5", "Apellido5", 22);
    listarEstudiante( &lista20, "Estudiante6", "Apellido6", 23);
    listarEstudiante( &lista20, "Estudiante7", "Apellido7", 24);
    listarEstudiante( &lista20, "Estudiante8", "Apellido8", 25);
    listarEstudiante( &lista20, "Estudiante9", "Apellido9", 26);
    listarEstudiante( &lista20, "Estudiante10", "Apellido10", 27);
    listarEstudiante( &lista20, "Estudiante11", "Apellido11", 28);
    listarEstudiante( &lista20, "Estudiante12", "Apellido12", 29);
    listarEstudiante( &lista20, "Estudiante13", "Apellido13", 30);
    listarEstudiante( &lista20, "Estudiante14", "Apellido14", 31);
    listarEstudiante( &lista20, "Estudiante15", "Apellido15", 32);
    listarEstudiante( &lista20, "Estudiante16", "Apellido16", 33);
    listarEstudiante( &lista20, "Estudiante17", "Apellido17", 34);
    listarEstudiante( &lista20, "Estudiante18", "Apellido18", 35);
    listarEstudiante( &lista20, "Estudiante19", "Apellido19", 36);
    listarEstudiante( &lista20, "Estudiante20", "Apellido20", 37);
    return lista20;
}

Materia *cincoMateriasTest(Materia* lista){
    Materia *listaMaterias = lista;
    listarMateria(&listaMaterias,"Materia Uno");
    listarMateria(&listaMaterias,"Materia Dos");
    listarMateria(&listaMaterias,"Materia Tres");
    listarMateria(&listaMaterias,"Materia Cuatro");
    listarMateria(&listaMaterias,"Materia Cinco");
    return listaMaterias;
}

