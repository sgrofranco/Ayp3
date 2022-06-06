#include <stdio.h>
#include <stdlib.h>
#import "Materia.c"


///TODO: GUARDAR NOMBRE DEL ALUMNO EN LOWER CASE PARA FACILITAR SU BUSQUEDA POR NOMBRE
typedef struct Alumno{
    long int numeroLegajo;
    char Nombre[30];
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
    strcpy(nuevoAlumno->Nombre, nombre);
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

void MostrarAlumnosPorRangoDeEdad(ListaDeAlumnos* listaDeAlumnos,int edadMinima,int edadMaxima){
    Alumno* alumno = listaDeAlumnos->cabeza;
    do{
        if(alumno->edad > edadMinima && alumno->edad < edadMaxima){
            printearAlumno(alumno);
        }
        alumno = alumno->siguiente;
    } while (alumno);
}

int puedeRendirMaterias(Alumno* alumno){  ///Return 0 significa que no tiene materias para rendir y return 1 quiere decir que si
    if(alumno->listaDeHistorialDeMaterias->cabeza == NULL){
        printf("El Alumno no esta inscripto a ninguna Materia \n");
        return 0;
    }else{
        int puedeRendir = 0 ;
        HistorialDeLaMateria* historialDeLaMateria = alumno->listaDeHistorialDeMaterias->cabeza;
        do {
            if(historialDeLaMateria->nota == NULL){
                if(puedeRendir == 0){
                    printf("---Materias que Puede rendir Este Alumno--- \n");
                }
                printf("Materia: %s ID: %li \n",historialDeLaMateria->infoMateria->nombreMateria,historialDeLaMateria->infoMateria->idMateria);
                puedeRendir++;
            }
            historialDeLaMateria = historialDeLaMateria->siguiente;
        } while (historialDeLaMateria);
        return puedeRendir;
    }
}

void printearListaDeAlumnos(ListaDeAlumnos* lista){
    Alumno* alumno = lista->cabeza;
    printf("-----LISTA DE ALUMNOS----\n");
    do{
        printf("--------------\n");
        printf("Nombre: %s \n",alumno->Nombre );
        printf("Edad: %i\n", alumno->edad);
        printf("Legajo N:%li\n",alumno->numeroLegajo);
        alumno = alumno->siguiente;
    } while (alumno != NULL);
    printf("-----==============----\n");

}

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

int nombreContieneBuscado(char nombreAlumno[],char nombreABuscar[]){
    int isPresent = 0;
    for (int i = 0; nombreAlumno[i] != '\0'; i++) {
        isPresent = 0;
        for (int j = 0; nombreABuscar[j] != '\0'; j++) {
            if (nombreAlumno[i + j] != nombreABuscar[j]) {
                isPresent = 0;
                break;
            }
            isPresent = 1;
        }
        if (isPresent) {
            break;
        }
    }
    return isPresent;
}

void buscarAlumnoPorNombre(ListaDeAlumnos* listaDeAlumnos,char nombreABuscar[]){
    Alumno* alumno = listaDeAlumnos->cabeza;
    if(nombreContieneBuscado(alumno->Nombre,nombreABuscar) == 1){
        printf("Alumno nombre: %s \n", alumno->Nombre);
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

void getPromedioAlumno(ListaDeAlumnos * lista,long int idAlumnoABuscar) {
    Alumno* alumno = getAlumno(lista,idAlumnoABuscar);
    if(alumno){
        int materiasRendidas = 0;
        int sumaMaterias = 0;
        if(alumno->listaDeHistorialDeMaterias->cabeza){
            HistorialDeLaMateria* historialDeLaMateria = alumno->listaDeHistorialDeMaterias->cabeza;
            do {
                if(historialDeLaMateria->nota){
                    materiasRendidas++;
                    sumaMaterias = sumaMaterias + historialDeLaMateria->nota;
                }
                historialDeLaMateria = historialDeLaMateria->siguiente;
            } while (historialDeLaMateria);
            ///TODO: QUE IMPRIMA UN FLOAT PARA QUE MUESTRE UN PROMEDIO MAS EXACTO
            printf("El promedio del alumno es: %i \n",sumaMaterias/materiasRendidas);
        }else{
            printf("El Alumno no rindio ninguna Materia \n");
        }
    }
}

/// TODO: Volver a cambiar este metodo para revisar las correlativas
void agregarMateriaAAlumno(Alumno* alumno, Materia* materia){
    if (alumno->listaDeHistorialDeMaterias->cabeza == NULL){
        alumno->listaDeHistorialDeMaterias->cabeza = CrearHsitorialDeLaMaateria(materia);
    } else {
        HistorialDeLaMateria* historialDeLaMateria = alumno->listaDeHistorialDeMaterias->cabeza;
        do {
            if(historialDeLaMateria->infoMateria->idMateria == materia->idMateria){
                break;
            } else if (historialDeLaMateria->siguiente){
                historialDeLaMateria = historialDeLaMateria->siguiente;
            } else {
                break;
            }
        } while (historialDeLaMateria);

        if(historialDeLaMateria->infoMateria->idMateria == materia->idMateria){
            if(historialDeLaMateria->nota != NULL){
                printf("ADVERTENCIA: Este Alumno ya rindio la Materia \n");
            }else{
                printf("ADVERTENCIA: Este Alumno ya se encuentra anotado a esta materia \n");
            }
        }else{
            HistorialDeLaMateria* nuevoHistorialDeLaMateria = CrearHsitorialDeLaMaateria(materia);
            historialDeLaMateria->siguiente = nuevoHistorialDeLaMateria;
        }
    }
}
///Este metodo le pasamos la Id de la materia que queremos averiguar si la tiene aprobada
///Si Returnea 0 quiere decir que no la tiene aprobada y 1 si la tiene aprobada
int VerificarMateriaAprobada(int idMateria , Alumno* alumno){
    HistorialDeLaMateria* materia = alumno->listaDeHistorialDeMaterias->cabeza;
    int materiaAprobada = 0;
    while(materia){
        if(materia->infoMateria->idMateria == idMateria){
            if(materia->nota != NULL){
                materiaAprobada++;
            } else {
                printf("El Alumno Esta Cursando %s , Que es una materia Correlativa \n",materia->infoMateria->nombreMateria);
            }
        }
        if(!materia->siguiente || materiaAprobada == 1){
            return materiaAprobada;
        }
        materia = materia->siguiente;
    }
}

///Este Metodo nos permite saber si el alumno tiene aprobadas las correlativas necesarias para Anotarse a esta materia
///Si returnea 0 quiere decir que puede anotarse a la materia , si returnea 1 quiere decir que le faltan aprobar algunas correlativas
int verificadorDeMateriasCorrelativas(Materia* materia,Alumno* alumno){
    int existenMateriasCorrelativasNoAprobadas = 0;
    int i = 0;
    while(materia->arrayCorrelativas[i]->idMateria != 0 && i < 5){
        if(materia->arrayCorrelativas[i]->idMateria){
            if(VerificarMateriaAprobada(materia->arrayCorrelativas[i]->idMateria,alumno) == 0){
                existenMateriasCorrelativasNoAprobadas++;
            }
            if(existenMateriasCorrelativasNoAprobadas != 0){
                return existenMateriasCorrelativasNoAprobadas;
            }
        }else{
            break;
        }
        i++;
    }
    return existenMateriasCorrelativasNoAprobadas;
}

//TODO: AHORA QUE EXISTEN LAS CORRELATIVAS TENEMOS QUE VOLVER A HACER ESTE METODO
void AnotarseAMateria(ListaMaterias* listaDeMaterias, ListaDeAlumnos* listaDeAlumnos, int idMateria, long int idAlumno){
    Materia* materia = getMateria(listaDeMaterias,idMateria);
    Alumno* alumno = getAlumno(listaDeAlumnos,idAlumno);
    if(verificadorDeMateriasCorrelativas(materia,alumno) == 0){
        agregarMateriaAAlumno(alumno,materia);
        printf("Se anoto al alumno %s a la materia %s \n",alumno->Nombre,materia->nombreMateria);
    } else{
        printf("por lo tanto no se puede anotar a la materia \n");
    }
}

void CargarNota(Alumno* alumno,Materia* materia){
    HistorialDeLaMateria* historialDeLaMateria = alumno->listaDeHistorialDeMaterias->cabeza;
    do {
        if(historialDeLaMateria->infoMateria->idMateria == materia->idMateria){
            break;
        }
        else if(historialDeLaMateria->siguiente){
            historialDeLaMateria = historialDeLaMateria->siguiente;
        } else {
            printf("ADVERTENCIA: No esta anotado a la materia, por lo que no puede rendirla\n");
            break;
        }
    } while (historialDeLaMateria);
    if(historialDeLaMateria->infoMateria->idMateria == materia->idMateria) {
        if (historialDeLaMateria->nota != NULL) {
            printf("ADVERTENCIA: Este Alumno ya rindio la Materia \n");
        } else {
            int nota = 0;
            do {
                printf("Que Nota Obtubo el alumno en el examen? \n");
                scanf("%i",&nota);
                if(nota > 10 || nota <1){
                    printf("ADVERTENCIA: La Nota no es valida, tiene que ser de 1 a 10 \n");
                }
            }while(nota > 10 || nota <1);
            if(nota < 4 ){
                ///Temporal
                ///TODO: ESTO DESTRUYE EL NODO DE LA MATERIA PERO EL PUNTERO DEL ANTERIOR APUNTA A BASURA
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
