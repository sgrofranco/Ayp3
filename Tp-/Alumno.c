#include <stdio.h>
#include <stdlib.h>
#import "Materia.c"

typedef struct Alumno{
    long int numeroLegajo;
    char *Nombre;
    int edad;
    struct ListaDeHistorialDeMaterias* listaDeHistorialDeMaterias;
    struct Alumno* siguiente;
} Alumno;

typedef struct ListaDeAlumnos{
    Alumno* cabeza;
    long int cantidadAlumnos;
} ListaDeAlumnos;

Alumno* CrearAlumno(char nombre[] , int edad){
    Alumno* nuevoAlumno = (struct Alumno*) malloc(sizeof (Alumno));
    nuevoAlumno->Nombre = nombre;
    nuevoAlumno->edad = edad;
    nuevoAlumno->siguiente  = NULL;
    nuevoAlumno->listaDeHistorialDeMaterias = (struct ListaDeHistorialDeMaterias*) malloc(sizeof (ListaDeHistorialDeMaterias));
    nuevoAlumno->listaDeHistorialDeMaterias->cabeza = NULL;
    return nuevoAlumno;
};

void printearAlumno(Alumno* alumno){
    printf("Nombre: %s \n",alumno->Nombre);
    printf("edad: %i \n",alumno->edad);
    printf("legajo: %li \n",alumno->numeroLegajo);
}

ListaDeAlumnos* inicializarListaAlumnos(){
    ListaDeAlumnos* listaAlumnos = (struct ListaDeAlumnos*) malloc(sizeof (struct ListaDeAlumnos));
    listaAlumnos->cantidadAlumnos = 0;
    listaAlumnos->cabeza = NULL;
    return listaAlumnos;
}

void printearListaDeAlumnos(ListaDeAlumnos* lista){
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
void agregarAlumno(ListaDeAlumnos* lista,char nombre[], int edad){
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

Alumno* getAlumno(ListaDeAlumnos* lista , long int idAlumno){
    Alumno* alumno = lista->cabeza;
    while (alumno->numeroLegajo != idAlumno && alumno->siguiente){
        alumno = alumno->siguiente;
    }
    if(alumno->numeroLegajo == idAlumno){
        return alumno;
    }
}

void agregarMateriaAAlumno(Alumno* alumno, Materia* materia){
    if (alumno->listaDeHistorialDeMaterias->cabeza == NULL){
        alumno->listaDeHistorialDeMaterias->cabeza = CrearHsitorialDeLaMaateria(materia);
    } else {
        HistorialDeLaMateria* historialDeLaMateria = alumno->listaDeHistorialDeMaterias->cabeza;
        do {
            if(historialDeLaMateria->infoMateria->idMateria == materia->idMateria){
                break;
            }
            historialDeLaMateria = historialDeLaMateria->siguiente;
        } while (historialDeLaMateria);
        if(historialDeLaMateria->infoMateria->idMateria == materia->idMateria){
            if(historialDeLaMateria->nota != NULL){
                printf("Este Alumno ya rindio la Materia \n");
            }else{
                printf("Este Alumno ya se encuentra anotado a esta materia \n");
            }
        }else{
            HistorialDeLaMateria* nuevoHistorialDeLaMateria = CrearHsitorialDeLaMaateria(materia);
            historialDeLaMateria->siguiente = nuevoHistorialDeLaMateria;
        }
    }
}

void AnotarseAMateria(ListaMaterias* listaDeMaterias, ListaDeAlumnos* listaDeAlumnos, int idMateria, long int idAlumno){
    Materia* materia = getMateria(listaDeMaterias,idMateria);
    Alumno* alumno = getAlumno(listaDeAlumnos,idAlumno);
    agregarMateriaAAlumno(alumno,materia);
}

void CargarNota(Alumno* alumno,Materia* materia){
    HistorialDeLaMateria* historialDeLaMateria = alumno->listaDeHistorialDeMaterias->cabeza;
    do {
        if(historialDeLaMateria->infoMateria->idMateria == materia->idMateria){
            break;
        }
        if(historialDeLaMateria->siguiente){
            historialDeLaMateria = historialDeLaMateria->siguiente;
        }
    } while (historialDeLaMateria);
    if(historialDeLaMateria->infoMateria->idMateria == materia->idMateria) {
        if (historialDeLaMateria->nota != NULL) {
            printf("Este Alumno ya rindio la Materia \n");
        } else {
            int nota = 0;
            do {
                printf("Que Nota Obtubo el alumno en el examen? \n");
                scanf("%i",&nota);
                if(nota > 11 && nota <0){
                    printf("La Nota no es valida, tiene que ser de 0 a 10 \n");
                }
            }while(nota > 11 && nota <0);
            if(nota < 4 ){
                destruirHistorialMateria(historialDeLaMateria);
            }else{
                historialDeLaMateria->nota = nota;
            }
            // el puntero siguiente del anterior como quedara?
            //nota de aprobado es 4
        }
    }
}
void RendirMateria(ListaDeAlumnos* listaDeAlumnos , ListaMaterias* listaDeMaterias,int idMateria , long int idAlumno){
    Materia* materia = getMateria(listaDeMaterias,idMateria);
    Alumno* alumno = getAlumno(listaDeAlumnos,idAlumno);
    CargarNota(alumno,materia);
}
