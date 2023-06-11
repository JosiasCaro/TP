# Trabajo Practico de Algoritmos y programación 3
Integrantes: Caro Josias, Saracco Lucas, Torres Agustin, Vazquez Marcos y Weber Federico.

## Consigna:

Desarrolar un sistema de estudiantes en C, capaz de interactuar y ejecutar una serie de acciones. Este sistema debe ser capaz de poder soportar un gran listado de estudiantes y materias utilizando estructuras de datos para almacenar los listados y utilizar ordenamiento de los datos si es necesario.

## Listado de consignas realiazadas en el trabajo.

#### Consignas básicas:
* Crear y listar estudiantes.
* Buscar estudiantes por nombre.
* Buscar estudiantes por rango de edad.
* Crear y listar materias.
* Anotarse en una materia.
* Rendir una materia.

#### Consignas extra: (Modificar con lo nuestro )
* Soporte de paginado(cada 5 estudiantes( agregar paginado a materias).).
* Generación masiva de estudiantes para testeo.
* Generación masiva de Materias para testeo.
* Promedios de cada alumno
* Lista ordenada por nombres de estudiantes.
* Ver información de estudiantes y sus materias.
* Diseño de menú?(Mejoras en la interfaz de usuario?). 


En el caso de la persistencia y la carga masiva, se realizaron testos de hasta 50000 alumnos y 50000 materias simultaneamente y si bien funcionaba, los tiempos de carga eran considerablemente altos. (modificar con lo nuestro)

## Desarollo: (Modificar con nuestra informacion)

Para empezar creamos los 2 struct esenciales, el struct "Alumno", el cual contenia informacion de este y un arrelgo de historial de materias, y el struct "Materia" que tambien contenia su informacion esencial y una lista de materias correlativas. Para esto ultimo, creamos un tercer struct "HistorialDeMateria", el cual consistia en una nota y un puntero a la materia de la cual es historial para obtener sus datos. 

A partir de estos elementos creamos las listas y creamos un menu en el cual se puede soliticar las acciones soportadas por cada una de las listas. Adicionalmente agregamos un archivo "Utilidades" el cual contiente todos los metodos auxiliares y aquellos metodos encargados de la persistencia.

## Resultado y Analisis: (Modificar con nuestra informacion)

## Conclusiones: (Modificar con nuestra informacion)
