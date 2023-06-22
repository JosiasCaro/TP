#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "Materia.c"

//---------------------------------------------TEST---------------------------------------------
Estudiante *veinteEstudiantesTest(Estudiante* lista){
    Estudiante *listaDe20Estudiantes = lista;
    listarEstudiante(&listaDe20Estudiantes, "Abril", "Aliendro", 18);
    listarEstudiante(&listaDe20Estudiantes, "Brenda", "Bolsonaro", 19);
    listarEstudiante(&listaDe20Estudiantes, "Carla", "Cabrera", 20);
    listarEstudiante(&listaDe20Estudiantes, "Damian", "Dorrego", 21);
    listarEstudiante(&listaDe20Estudiantes, "Emanuel", "Erviti", 22);
    listarEstudiante(&listaDe20Estudiantes, "Facundo", "Fernandez", 23);
    listarEstudiante(&listaDe20Estudiantes, "Gaston", "Gutierrez", 24);
    listarEstudiante(&listaDe20Estudiantes, "Horacio", "Hernandez", 25);
    listarEstudiante(&listaDe20Estudiantes, "Ines", "Ibrahimovic", 26);
    listarEstudiante(&listaDe20Estudiantes, "Jazmin", "Jimenez", 27);
    listarEstudiante(&listaDe20Estudiantes, "Karina", "Kvaratskhelia", 28);
    listarEstudiante(&listaDe20Estudiantes, "Lorena", "Lavezzi", 29);
    listarEstudiante(&listaDe20Estudiantes, "Manuel", "Merentiel", 30);
    listarEstudiante(&listaDe20Estudiantes, "Nicolas", "Nocino", 31);
    listarEstudiante(&listaDe20Estudiantes, "Omar", "Orsini", 32);
    listarEstudiante(&listaDe20Estudiantes, "Paulo", "Palacios", 33);
    listarEstudiante(&listaDe20Estudiantes, "Quique", "Quintero", 34);
    listarEstudiante(&listaDe20Estudiantes, "Roman", "Riquelme", 35);
    listarEstudiante(&listaDe20Estudiantes, "Sebastian", "Saliba", 36);
    listarEstudiante(&listaDe20Estudiantes, "Tomas", "Taglafico", 37);
    return listaDe20Estudiantes;
}

Materia *cincoMateriasTest(Materia* lista){
    Materia *listaMaterias = lista;
    listarMateria(&listaMaterias,"Analisis_matematicoI");
    listarMateria(&listaMaterias,"FisicaI");
    listarMateria(&listaMaterias,"Electronica");
    listarMateria(&listaMaterias,"Algoritmos_y_programacionI");
    listarMateria(&listaMaterias,"AlgebraI");
    return listaMaterias;
}

//---------------------------------------------FUNCIONES EXTRAS DE MATERIAS---------------------------------------------
void generarMateriasAleatorias(Materia *listaDeMaterias, int maximo, int mostrar) {

    Materia **listaMateria = (&listaDeMaterias);
    char* listaNombres[]={ "Algoritmos_y_programacionI","Estructura_de_datos", "Base_de_datos", "Analisis_matematicoI",
                           "Algebra","Fisica","Sistemas_de_representacion","Arquitectura_de_computadoras",
                           "minecraft_tecnico", "Electronica", "Historia", "Filosofia", "Disenio_grafico",
                           "Quimica","Teoria_de_la_organizacion", "Finanzas", "Impuestos","Derecho", "Defensa_oral_y_escrita",
                           "Robotica", "Probabilidad_y_estadistica", "Matematica_discreta", "Sistema_monetario",
                           "Teoria_de_juegos"};

    int i;

    if (maximo <= 0 || maximo > sizeof(listaNombres)/sizeof(listaNombres[0])) {
        printf("Cantidad invalida. Debe ser un numero entre 1 y %d.\n", sizeof(listaNombres)/sizeof(listaNombres[0]));
    }

    // Inicializar la semilla para generar nombres aleatorios
    srand(time(NULL));

    printf("Materias generadas.\n");
    for (i = 0; i < maximo; i++) {
        int indiceMateriaAleatorio = rand() % sizeof(listaNombres)/sizeof(listaNombres[0]);
        int edad = rand() % (100 - 17 + 1) + 17;
        listarMateria(listaMateria, listaNombres[indiceMateriaAleatorio]);
        if(mostrar == 1) {
            printf("%s\n", listaNombres[indiceMateriaAleatorio]);
        }
    }
}

int cantidadDeMaterias(Materia *lista) {
    int contador = 0;
    while(lista != NULL){
        contador++;
        lista= lista->sig;
    }
    return contador;
}

void imprimirDatosDeMateria(Materia *actual, int i, int b){
    printf("[%d] Nombre de la materia:%s \n",i, actual->nombreMateria);
    Materia *materiaActual = actual->materiasCorrelativas;
    printf("-----------------------------------------------\n");
    if(materiaActual != NULL) {
        printf("   Nombres de las materias Correlativas a %s:\n",actual->nombreMateria);
        while(materiaActual != NULL) {
            printf("   %s\n",materiaActual->nombreMateria);
            materiaActual = materiaActual->sig;
        }
    }else {
        printf("   La materia no tiene correlativas.\n");
    }
    printf("-----------------------------------------------\n");
}

void imprimirListaDeMateriasPaginadas(Materia *lista){
    int i=1, b=1;
    Materia *actual;
    actual = lista;

    int cantidad = cantidadDeMaterias(lista);

    if(cantidad > 5) { //Cambiar este 5 estatico
        int contadorActual = 0;
        int contadorF = 0;
        int vuelve = 0;

        while(actual != NULL && vuelve == 0){
            if(contadorActual < 5){
                imprimirDatosDeMateria(actual, i, b);
                contadorActual += 1;
                contadorF += 1;
                actual = actual->sig;
                i += 1;
                b += 1;
            }
            if(contadorF == cantidad) {
                char respuesta[1];
                printf("\nSe han mostrado todos los estudiantes, por favor presione la tecla numero 1 para volver al menu...\n");
                scanf("%s", respuesta);
                if(strcmp(respuesta,"1") == 0){
                    vuelve = 1;
                }
            }else if(contadorActual == 5 && actual != NULL){
                contadorActual = 0;
                char respuesta[1];
                printf("\nPresione cualquier numero para ir a la pagina siguiente o la tecla numero 1 para volver al menu...\n");
                scanf("%s", respuesta);
                if(strcmp(respuesta,"1") == 0){
                    vuelve = 1;
                }
            }
        }
    }else{
        while(actual != NULL){
            imprimirDatosDeMateria(actual, i, b);
            b++;
            i++;
            actual = actual->sig;
        }
    }
}

void imprimirListaMaterias(Materia *lista){
    while(lista!=NULL){
        printf("%s\n", lista->nombreMateria);
        lista = lista->sig;
    }
}

//---------------------------------------------FUNCIONES EXTRAS DE ESTUDIANTES---------------------------------------------
void generarAlumnosAleatorios(Estudiante *listaDeAlumnos, int maximo, int mostrar) {

    Estudiante **listaAlumnos = (&listaDeAlumnos);
    char *listaNombres[]= {"Adel","Adonis","Ajaz","Akos","Aldo","Amets","Amaro","Aquiles","Algimantas","Alpidio","Amrane","Anish","Arian","Ayun","Azariel","Bagrat"
            ,"Bencomo","Bertino","Candi","Cesc","Cirino","Crisologo","Cruz","Danilo","Dareck","Dariel","Darin","Delmiro","Damen","Dilan","Dipa"
            ,"Domenico","Drago","Edivaldo","Elvis","Elyan","Emeric","Engracio","Ensa","Enaut","Eleazar","Eros","Eufemio","Feiyang"
            ,"Fiorenzo","Foudil","Galo","Gaston","Giulio","Gautam","Gentil","Gianni","Gianluca","Giorgio","Gourav","Grober","Guido"
            ,"Guifre","Guim","Hermes","Inge","Irai","Iraitz","Iyad","Iyan","Jeremias","Joao","Jun","Khaled","Leonidas","Lier","Lionel"
            ,"Lisandro","Lucian","Mael","Misael","Moad","Munir","Nael","Adara","Agata","Agripina","Ainhara","Aixa","Alegria","Alia","Alla","America","Aminata","Amor","Anahi","Ania","Aquilina","Ariadne","Arya","Asia","Atenea","Bella"};

    char *listaDeApellidos[]={"Gonzalez","Rodriguez","Gomez","Fernandez","Lopez","Martinez","Diaz","Perez","Sanchez"
            ,"Romero","Garcia","Sosa","Benitez","Ramirez","Torres","Ruiz","Flores","Alvarez","Acosta","Rojas"};

    int i;

    if (maximo <= 0 || maximo > sizeof(listaNombres)/sizeof(listaNombres[0])) {
        printf("Cantidad invalida. Debe ser un numero entre 1 y %d.\n", sizeof(listaNombres)/sizeof(listaNombres[0]));
    }

    // Inicializar la semilla para generar nombres aleatorios
    srand(time(NULL));

    printf("Alumnos generados.\n");
    for (i = 0; i < maximo; i++) {
        int indiceNombreAleatorio = rand() % sizeof(listaNombres)/sizeof(listaNombres[0]);
        int indiceApellidoAleatorio = rand() % sizeof(listaDeApellidos)/sizeof(listaDeApellidos[0]);
        int edad = rand() % (100 - 17 + 1) + 17;
        listarEstudiante(listaAlumnos,listaNombres[indiceNombreAleatorio],listaDeApellidos[indiceApellidoAleatorio], edad);
        if(mostrar == 1) {
            printf("%s %s %d\n", listaNombres[indiceNombreAleatorio], listaDeApellidos[indiceApellidoAleatorio], edad);
        }
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
        printf("Estado de la materia: %s\n",materiaActual->estadoMateria);
        printf("Nota de la materia: %d\n",materiaActual->notaMateria);
        printf("-----------------------------------------------\n");
        materiaActual = materiaActual->sig;
    }
}

void imprimirListaDeEstudiantesPaginados(Estudiante *lista){
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

//Imprime la informacion del estudiante y las materias asociadas al mismo
Estudiante *infoEstudiante(Estudiante *primero, char nombreEstudiante[30],char apellidoEstudiante[30]){
    Estudiante *actual = primero;
    while(actual != NULL){
        if((strcmp(actual->nombreEstudiante,nombreEstudiante) == 0 ) && (strcmp(actual->apellidoEstudiante, apellidoEstudiante) == 0)){
            //printf("Materia encontrada:%s\n",actual->lista_materias->nombreDeLaMateria);
            Materia *nodo = actual->listaMaterias;
            printf("\nMaterias de %s:\n\n", actual->nombreEstudiante);
            while(nodo != NULL){
                printf("Materia: %s, estado: %s, nota: %d\n", nodo->nombreMateria, nodo->estadoMateria, nodo->notaMateria);
                nodo = nodo->sig;
            }
            return actual;
        }
        actual = actual->sig;
    }
    return (NULL);
}