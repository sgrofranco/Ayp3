# Trabajo Practico de Algoritmos y programación 3
Integrantes: Franco Sgro y Lucas Espindola.

## Consigna:

Crear un sistema de estudiantes en C, que consistia de 2 listas que interacturan entre si y pudieran ejecutar una serie de acciones.

## Desarollo:

Para empezar creamos los 2 struct esenciales, el struct "Alumno", el cual contenia informacion de este y un arrelgo de historial de materias, y el struct "Materia" que tambien contenia su informacion esencial y una lista de materias correlativas. Para esto ultimo, creamos un tercer struct "HistorialDeMateria", el cual consistia en una nota y un puntero a la materia de la cual es historial para obtener sus datos. 

A partir de estos elemenos creamos las listas y creamos un menu en el cual se puede soliticar las acciones soportadas por cada una de las listas. Adicionalmente agregamos un archivo "Utildiades" el cual contiente todos los metodos auxiliares y aquellos metodos encargados de la persistencia.

## Listado de consignas realiazadas en el trabajo.

#### Consignas básicas:
* Crear y listar estudiantes.
* Buscar estudiantes por nombre.
* Buscar estudiantes por rango de edad.
* Crear y listar materias.
* Anotarse en una materia.
* Rendir una materia.

#### Consignas extra:
* Soporte de paginado(Con posibilidad de elegir la página y la cantidad de items por c/u).
* Generación masiva de estudiantes para testeo (Usar opcion "99", modo desarrolaldor).
* Generación masiva de Materias para testeo (Usar opcion "99", modo desarrolaldor).
* Soporte de correlatividad para cada materia
* Promedios de cada alumno
* Persistencia
* Varias validaciones complejas
