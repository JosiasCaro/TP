#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Materia.c"

void menu(Estudiante *lista, Materia *listaMaterias) {
    int opcion;

    char nombreEstudiante[30];
    char apellidoEstudiante[30];
    int edadEstudiante;

    char nombreABuscar[30];
    char apellidoABuscar[30];

    int edadMax;
    int edadMin;

    char nombreMateria[30];
    char nombreMateriaCorrelativa[30];
    // "As" al final porque son el nombre y apellido el estudiante al que se le asigna materia
    char nombreEstudianteAs[30];
    char apellidoEstudianteAs[30];

    int notaMateria;

    char nombreMateriaNueva[30];

    do{
        printf("\n-----Menu-----\n");
        printf("1. Listar estudiante \n");
        printf("2. Ver estudiantes \n");
        printf("3. Buscar estudiante \n");
        printf("4. Buscar estudiantes por rango etario \n");
        printf("5. Listar materia \n");
        printf("6. Ver materias \n");
        printf("7. Asignar materia \n");
        printf("8. Rendir materia \n");
        printf("9. Ver informacion completa de estudiantes y sus materias \n");
        printf("10. Calcular promedio de estudiantes \n");
        printf("11. Salir \n");

        scanf("%d", &opcion);

        switch (opcion){
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

            case 2:
                printf( "\n" );
                imprimirListaEstudiantes(lista);
                break;

            case 3:
                printf( "\n" );
                printf("Inserte el nombre del estudiante a buscar:\n");
                scanf("%s",nombreABuscar);
                printf("Inserte el apellido del estudiante a buscar:\n");
                scanf("%s",apellidoABuscar);
                Estudiante *temporal20 = NULL;
                temporal20 = buscarPorNombreYApellido(lista, nombreABuscar, apellidoABuscar);
                infoEstudiante(temporal20,nombreABuscar,apellidoABuscar);
                break;

            case 4:
                printf("\nInserte edad minima:\n");
                scanf("%d",&edadMin);
                printf("\nInserte edad maxima\n");
                scanf("%d",&edadMax);
                buscarPorRangoEtario(lista, edadMin, edadMax);
                break;

            case 5:
                printf( "\n");
                printf("Inserte nombre de la materia a listar:\n");
                scanf("%s",nombreMateriaNueva);
                listarMateria(&listaMaterias,nombreMateriaNueva);
                break;

            case 6:
                printf( "\n" );
                imprimirListaMaterias(listaMaterias);
                break;

            case 7:
                printf( "\n" );
                Estudiante *temp = NULL;
                printf("Inserte nombre del estudiante\n");
                scanf("%s", nombreEstudianteAs);
                printf("Inserte apellido del estudiante\n");
                scanf("%s",apellidoEstudianteAs);
                temp = buscarPorNombreYApellido(lista,nombreEstudianteAs,apellidoEstudianteAs);
                if(temp != 0){
                    printf("Inserte nombre de la materia\n");
                    scanf("%s",nombreMateria);
                    printf("Inserte nombre de la materia correlativa\n");
                    scanf("%s",nombreMateriaCorrelativa);
                    asignarMateria(temp,nombreMateria,nombreMateriaCorrelativa);
                }

                break;

            case 8:
                printf("Inserte nombre del alumno\n");
                scanf("%s", nombreABuscar);
                printf("Inserte apellido del alumno\n");
                scanf("%s", apellidoABuscar);
                printf("Inserte nombre de la materia\n");
                scanf("%s",nombreMateria);
                printf("Nota de %s %s en %s:\n", nombreABuscar, apellidoABuscar, nombreMateria);
                scanf("%d", &notaMateria);
                Estudiante *temp2 = NULL;
                temp2 = buscarPorNombreYApellido(lista, nombreABuscar, apellidoABuscar);
                rendirMateria(&temp2, nombreABuscar, apellidoABuscar, nombreMateria, notaMateria);
                break;

            case 9:
                imprimirLista(lista);
                break;

            case 10:
                printf("Inserte nombre del alumno\n");
                scanf("%s", nombreABuscar);
                printf("Inserte apellido del alumno\n");
                scanf("%s", apellidoABuscar);
                calcularPromedio(&lista,nombreABuscar,apellidoABuscar);
                break;

        }

    }while(opcion != 11);
}

int main(){
    Estudiante *lista = NULL;
    lista = (Estudiante *) veinteEstudiantesTest(lista);
    Materia *listaMateria = NULL;
    listaMateria = (Materia*) cincoMateriasTest(listaMateria);
    printf("\nPara comenzar a operar inserte el numero de la opcion con la cual desee interactuar");
    menu(lista, listaMateria);
}
