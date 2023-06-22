#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "FuncionesExtra.c"

void menuEstudiantes(Estudiante *lista, Materia *listaMaterias) {
    int opcion;

    char nombreEstudiante[30];
    char apellidoEstudiante[30];
    int edadEstudiante;

    int edadMax;
    int edadMin;

    char nombreMateria[30];

    int notaMateria;

    int max;
    int mostrar;

    do{
        printf("\n-----Menu de Estudiantes-----\n");
        printf("1. Listar estudiante \n");
        printf("2. Ver estudiantes \n");
        printf("3. Buscar estudiante \n");
        printf("4. Buscar estudiantes por rango etario \n");
        printf("5. Asignar materia \n");
        printf("6. Rendir materia \n");
        printf("7. Ver informacion completa de estudiantes y sus materias \n");
        printf("8. Calcular promedio de estudiantes \n");
        printf("9. Generar Alumnos aleatoreos\n");
        printf("10. Volver al Menu Principal \n");

        scanf("%d", &opcion);

        switch (opcion){
            //Listar estudiante
            case 1:
                printf( "\n" );
                printf("Inserte el nombre del estudiante:\n");
                scanf("%s",nombreEstudiante);
                printf("Inserte el apellido del estudiante:\n");
                scanf("%s",apellidoEstudiante);
                printf("Inserte la edad del estudiante\n");
                scanf("%d",&edadEstudiante);
                listarEstudiante(&lista,nombreEstudiante,apellidoEstudiante,edadEstudiante);
                break;

            //Ver estudiantes
            case 2:
                printf("\n");
                imprimirListaEstudiantes(lista);
                break;

            //Buscar estudiante
            case 3:
                printf( "\n" );
                printf("Inserte el nombre del estudiante a buscar:\n");
                scanf("%s",nombreEstudiante);
                printf("Inserte el apellido del estudiante a buscar:\n");
                scanf("%s",apellidoEstudiante);
                Estudiante *temporal20 = NULL;
                temporal20 = buscarPorNombreYApellido(lista, nombreEstudiante, apellidoEstudiante);
                if(temporal20 != NULL) {
                    printf("\nEstudiante encontrado: %s %s\n",temporal20->nombreEstudiante, temporal20->apellidoEstudiante);
                    infoEstudiante(temporal20,nombreEstudiante,apellidoEstudiante);
                }
                break;

            //Buscar estudiantes por rango etario
            case 4:
                printf("\nInserte edad minima:\n");
                scanf("%d",&edadMin);
                printf("\nInserte edad maxima\n");
                scanf("%d",&edadMax);
                buscarPorRangoEtario(lista, edadMin, edadMax);
                break;

            //Asignar materia
            case 5:
                printf( "\n" );
                Estudiante *estudiante = NULL;
                printf("Inserte nombre del estudiante\n");
                scanf("%s", nombreEstudiante);
                printf("Inserte apellido del estudiante\n");
                scanf("%s",apellidoEstudiante);
                estudiante = buscarPorNombreYApellido(lista,nombreEstudiante,apellidoEstudiante);
                if(estudiante != NULL) {
                    printf("Inserte nombre de la materia\n");
                    scanf("%s",nombreMateria);
                    Materia* materia = buscarMateria(listaMaterias, nombreMateria);
                    if(materia == NULL) {
                        printf("Materia no existente en la lista de materias.\n");
                    } else {
                        if(verificarQueTengaLasCorrelativasAprobadas(estudiante, materia) == 1) {
                            asignarMateria(estudiante,nombreMateria);
                        } else {
                            printf("Para anotarse a la materia debe aprobar sus correlativas");
                        }
                    }
                }
                break;
            
            //Rendir materia
            case 6:
                printf("Inserte nombre del alumno\n");
                scanf("%s", nombreEstudiante);
                printf("Inserte apellido del alumno\n");
                scanf("%s", apellidoEstudiante);
                printf("Inserte nombre de la materia\n");
                scanf("%s",nombreMateria);
                printf("Nota de %s %s en %s:\n", nombreEstudiante, apellidoEstudiante, nombreMateria);
                scanf("%d", &notaMateria);
                Estudiante *temp2 = buscarPorNombreYApellido(lista, nombreEstudiante, apellidoEstudiante);
                if(temp2 != NULL) {
                    rendirMateria(temp2, nombreEstudiante, apellidoEstudiante, nombreMateria, notaMateria);
                }
                break;

            //Ver informacion completa de estudiantes y sus materias
            case 7:
                imprimirListaDeEstudiantesPaginados(lista);
                break;

            //Calcular promedio de estudiantes.
            case 8:
                printf("Inserte nombre del alumno\n");
                scanf("%s", nombreEstudiante);
                printf("Inserte apellido del alumno\n");
                scanf("%s", apellidoEstudiante);
                calcularPromedio(&lista,nombreEstudiante,apellidoEstudiante);
                break;
            
            //Generar estudiantes aleatorios.
            case 9:
                printf("Ingrese la cantidad de Alumnos a generar:\n");
                scanf("%d", &max);
                printf("Ingrese si quiere ver el listado de alumnos generados (0)NO (1)Si:\n");
                scanf("%d", &mostrar);
                generarAlumnosAleatorios(lista, max, mostrar);
                break;
        }

    //Salir
    }while(opcion != 10);

}

void menuMaterias(Estudiante *lista, Materia *listaMaterias) {
    int opcion;

    char nombreMateria[30];

    int tieneCorrelativas;

    int max;
    int mostrar;

    do{
        printf("\n-----Menu de Materias-----\n");
        printf("1. Listar materia \n");
        printf("2. Ver materias \n");
        printf("3. Calcular estadistica de estudiantes en una materia\n");
        printf("4. Generar Materias aleatoreas\n");
        printf("5. Ver paginado materias\n");
        printf("6. Volver al Menu Principal \n");

        scanf("%d", &opcion);

        switch (opcion){
            //Listar materia
            case 1:
                printf( "\n");
                printf("Inserte nombre de la materia a listar (cambiando los espacios por guiones bajos \"_\"):\n");
                scanf("%s",nombreMateria);
                listarMateria(&listaMaterias, nombreMateria);
                do {
                    printf("La materia %s tiene correlativas? (0)NO (1)SI\n", nombreMateria);
                    scanf("%d", &tieneCorrelativas);
                    if(tieneCorrelativas == 1) {
                        Materia *materia = buscarMateria(listaMaterias, nombreMateria);
                        agregarMateriaCorrelativa(listaMaterias, materia);
                    }
                } while(tieneCorrelativas == 1);

                break;

            //Ver materias
            case 2:
                printf( "\n" );
                imprimirListaMaterias(listaMaterias);
                break;
            //
            case 3:
                calcularEstadisticaDeAlumnosEnUnaMateria(listaMaterias, lista);
                break;
            //
            case 4:
                printf("Ingrese la cantidad de Materias a generar:\n");
                scanf("%d", &max);
                printf("Ingrese si quiere ver el listado de materias generadas (0)NO (1)Si:\n");
                scanf("%d", &mostrar);
                generarMateriasAleatorias(listaMaterias, max, mostrar);
                break;
            //
            case 5:
                imprimirListaDeMateriasPaginadas(listaMaterias);
                break;

        }

    //Salir
    }while(opcion != 6);

}

void menu(Estudiante *lista, Materia *listaMaterias) {
    int opcion;

    do{
        printf("\n-----Menu-----\n");
        printf("1. Opciones para Estudiantes \n");
        printf("2. Opciones para Materias \n");
        printf("3. Salir \n");

        scanf("%d", &opcion);

        switch (opcion){
            //Ver Menu de Estudiantes
            case 1:
                menuEstudiantes(lista, listaMaterias);
                break;

            //Ver Menu de Materias
            case 2:
                menuMaterias(lista, listaMaterias);
                break;
        }

    //Salir
    }while(opcion != 3);
}

int main(){
    Estudiante *lista = NULL;
    lista = (Estudiante *) veinteEstudiantesTest(lista);
    Materia *listaMateria = NULL;
    listaMateria = (Materia*) cincoMateriasTest(listaMateria);
    printf("\nPara comenzar a operar inserte el numero de la opcion con la cual desee interactuar");
    menu(lista, listaMateria);
}

