#include <stdio.h>
#include <stdlib.h>

typedef struct Materia{
    int idMateria;
    char *nombreMateria;
    int nota;
    struct Materia* materiasCorrelativas[10];
} Materia;

typedef struct HistorialMaterias{
    int nota; // if nota == Null esta anotado , if nota != Null Rindo bien; si rinde mal se borra.
    Materia* materia;
};

typedef struct ListaMaterias{
    int cantidadMaterias;
    Materia* cabeza;
}ListaMaterias;

