#include <stdio.h>
#include <stdlib.h>
#import "Materia.c"

typedef struct Alumno{
    long int numeroLegajo;
    char *Nombre;
    int edad;
    struct HistorialMaterias* HistorialMaterias; // Array De materiasRendidas
    struct Alumno* siguiente;
} Alumno;

typedef struct ListaAlumnos{
    Alumno* cabeza;
    long int cantidadAlumnos;
}ListaAlumnos;

Alumno* CrearAlumno(char nombre[] , int edad){
    Alumno* nuevoAlumno = (struct Alumno*) malloc(sizeof (Alumno));
    nuevoAlumno->Nombre = nombre;
    nuevoAlumno->edad = edad;
    nuevoAlumno->siguiente  = NULL;
}

void printearAlumno(Alumno* alumno){
    printf("Nombre: %s \n",alumno->Nombre);
    printf("edad: %i \n",alumno->edad);
    printf("legajo: %li \n",alumno->numeroLegajo);
}

void printearLista(ListaAlumnos* lista){
    Alumno* alumno = lista->cabeza;
    do{
        printf("--------------\n");
        printf("Nombre: %s \n",alumno->Nombre );
        printf("Edad: %i\n", alumno->edad);
        printf("Legajo N:%li\n",alumno->numeroLegajo);
        alumno = alumno->siguiente;
    } while (alumno != NULL);
};

//Aca podemos implementar otro metodo ya que no necesita estar ordenado
//de esta forma lo ubica siempre en el fondo ordenado por el numero de legajo
//pero si lo agregamos siempre al principo no es necesario recorrerlo siempre
void agregarAlumno(ListaAlumnos* lista,char nombre[], int edad){
    if(lista->cabeza == NULL){
        lista->cantidadAlumnos++;
        Alumno* nuevoAlumno = CrearAlumno(nombre,edad);
        lista->cabeza = nuevoAlumno;
        nuevoAlumno->numeroLegajo = lista->cantidadAlumnos;
    }else{
        Alumno* alumno = lista->cabeza;
        while(alumno->siguiente){
            alumno = alumno->siguiente;
        }
        lista->cantidadAlumnos++;
        Alumno* nuevoAlumno = CrearAlumno(nombre,edad);
        nuevoAlumno->numeroLegajo = lista->cantidadAlumnos;
        alumno->siguiente = nuevoAlumno;
    }

}