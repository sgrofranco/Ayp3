///TODO: aca va a estar la bdd, el generador masivo de alumnos
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///PRE: se le ingresa la lista de alumnos y la cantidad de alumnos que se desean crear
///POST: modifica la lista ingresada con los nuevos alumnos generados aleatoriamente
void generarAlumnosAleatorios(ListaDeAlumnos* listaDeAlumnos, int maximo,int mostrar){
    char *listaNombres[]= {"Adel","Adonis","Ajaz","Akos","Aldo","Amets","Amaro","Aquiles","Algimantas","Alpidio","Amrane","Anish","Arian","Ayun","Azariel","Bagrat"
            ,"Bencomo","Bertino","Candi","Cesc","Cirino","Crisologo","Cruz","Danilo","Dareck","Dariel","Darin","Delmiro","Damen","Dilan","Dipa"
            ,"Domenico","Drago","Edivaldo","Elvis","Elyan","Emeric","Engracio","Ensa","Enaut","Eleazar","Eros","Eufemio","Feiyang"
            ,"Fiorenzo","Foudil","Galo","Gaston","Giulio","Gautam","Gentil","Gianni","Gianluca","Giorgio","Gourav","Grober","Guido"
            ,"Guifre","Guim","Hermes","Inge","Irai","Iraitz","Iyad","Iyan","Jeremias","Joao","Jun","Khaled","Leonidas","Lier","Lionel"
            ,"Lisandro","Lucian","Mael","Misael","Moad","Munir","Nael","Adara","Agata","Agripina","Ainhara","Aixa","Alegria","Alia","Alla","America","Aminata","Amor","Anahi","Ania","Aquilina","Ariadne","Arya","Asia","Atenea","Bella"};

    char *listaDeApellidos[]={"Gonzalez","Rodriguez","Gomez","Fernandez","Lopez","Martinez","Diaz","Perez","Sanchez"
            ,"Romero","Garcia","Sosa","Benitez","Ramirez","Torres","Ruiz","Flores","Alvarez","Acosta","Rojas"};

    for(int i = 0 ; i < maximo ; i++){
        int nombre = -1;
        int apellido = 0;
        int edad = 10;

        while(nombre<=0 || nombre > (sizeof listaNombres / sizeof listaNombres[0])){
            nombre = rand() % sizeof listaNombres / sizeof listaNombres[0];
        }
        char *nombreAlumno = listaNombres[nombre];
        while(apellido<=0 || apellido > (sizeof listaDeApellidos / sizeof listaDeApellidos[0])){
            apellido = rand() % sizeof listaDeApellidos / sizeof listaDeApellidos[0];
        }
        char *apellidoAlumno = listaDeApellidos[apellido];
        while(edad < 17 || edad > 100){
            edad = rand() % 100;
        }

        char nombreCompleto[50];

        strcpy(nombreCompleto, nombreAlumno);
        strcat(nombreCompleto,  apellidoAlumno);

        agregarAlumno(listaDeAlumnos,nombreCompleto,edad);
        if(mostrar == 1){
            printf("alumno: %s , edad: %i \n",nombreCompleto,edad);
        }
    }
}

///PRE: se le Ingresa la lista de Materias y la cantidad de materias que se desean generar aleatoreamente
///POST: Modifica la lista ingresada con las nuevas materias generadas aleatoriamente
void generarMateriasAleatorias(ListaMaterias* listaMaterias, int maximo,int mostrar){

    char* listaNombres[]={ "Algoritmos y programacion","Estructura de datos", "Base de datos", "Analisis matematico",
                           "Algebra","Fisica","Sistemas de representacion","Arquitectura de computadoras",
                           "minecraft tecnico", "Electronica", "Historia", "Filosofia", "Disenio grafico",
                           "Quimica","Teoria de la organizacion", "Finanzas", "Impuestos","Derecho", "Defensa oral y escrita",
                           "Robotica", "Probabilidad y estadistica", "Matematica discreta", "Sistema monetario",
                           "Teoria de juegos"};

    char* listaDeNivel[]={ "1","2","3","4","5","6"};

    for (int i = 0; i < maximo; i++){
        int nombre = 0;
        int nivel = -1;

        while(nombre <= 0 || nombre > (sizeof listaNombres/sizeof listaNombres[0])){
            nombre = rand() % sizeof listaNombres/sizeof  listaNombres[0];
        }
        char* nombreDeMateria = listaNombres[nombre];

        while (nivel < 0 || nivel > 5){
            nivel = rand() %5;
        }
        char* nivelDefinitivo = listaDeNivel[nivel];


        char nombreCompleto[50];

        strcpy(nombreCompleto, nombreDeMateria);
        strcat(nombreCompleto, " ");
        strcat(nombreCompleto, nivelDefinitivo);

        agregarMateriaAListaDeMateriasSinCorrelativas(listaMaterias,nombreCompleto);

        if(mostrar == 1){
            printf("materia: %s \n",nombreCompleto);
        }

    }
}


void cargarHistorialAlAlumno(ListaMaterias* listaMaterias,ListaDeAlumnos* listaDeAlumnos,long int idalumno , int idMateria , int nota){
    Alumno* alumno = getAlumno(listaDeAlumnos,idalumno);
    Materia* materia = getMateria(listaMaterias,idMateria);
    agregarMateriaAAlumno(alumno,materia,1);
    HistorialDeLaMateria* historialDeLaMateria = alumno->listaDeHistorialDeMaterias->cabeza;
    if(nota != 0){
        do {
            if(historialDeLaMateria->infoMateria->idMateria == materia->idMateria){
                break;
            }
            else if(historialDeLaMateria->siguiente){
                historialDeLaMateria = historialDeLaMateria->siguiente;
            }
        } while (historialDeLaMateria);
        historialDeLaMateria->nota = nota;
    }else{
        historialDeLaMateria->nota = NULL;
    }
};

void InicializarBdd(ListaDeAlumnos* listaDeAlumnos, ListaMaterias* listaMaterias){
    ///bdd Materia
    printf("Cargando BDD Materia... \n");
    FILE* fileBddMaterias;
    fileBddMaterias = fopen("../bddMaterias.txt","r");
    char lineBddMateria [128] = {0};
    int lineaActualMateria = 0;
    if(!fileBddMaterias){
        printf("No cargo la bdd llame a su tecnico mas cercano \n");
    }
    while (fgets(lineBddMateria , 128 , fileBddMaterias)){
        lineaActualMateria++;
        char* lineaSplitMateria = strtok(lineBddMateria,",");
        char nombreMateria[30];
        strcpy(nombreMateria,lineaSplitMateria);
        lineaSplitMateria = strtok(NULL,",");
        if(listaMaterias->cabeza == NULL){///Esto es lo mismo que agregar materia a lista de materia
            listaMaterias->cantidadMaterias++;
            Materia* nuevaMateria = crearMateria(nombreMateria);
            nuevaMateria->idMateria = listaMaterias->cantidadMaterias;
            listaMaterias->cabeza = nuevaMateria;
        }else{
            Materia* materia = listaMaterias->cabeza;
            while(materia->siguiente){
                materia = materia->siguiente;
            }
            listaMaterias->cantidadMaterias++;
            Materia* nuevaMateria = crearMateria(nombreMateria);
            nuevaMateria->idMateria = listaMaterias->cantidadMaterias;
            materia->siguiente = nuevaMateria;
        }
        while(lineaSplitMateria != NULL){
            char correlativas[40];
            char *puntero;
            Materia* materia = getMateria(listaMaterias,lineaActualMateria);
            strcpy(correlativas,lineaSplitMateria);
            puntero = strtok(correlativas,":");
            while(puntero != NULL){
                int idMateriaCorrelativa;
                idMateriaCorrelativa = atoi(puntero);
                if(idMateriaCorrelativa != 0){
                    if(puntero){
                        int i = 0;
                        while (materia->arrayCorrelativas[i]->idMateria != 0) {
                            i++;
                        }
                        materia->arrayCorrelativas[i] = getMateria(listaMaterias, idMateriaCorrelativa);
                    }
                }
                puntero = strtok(NULL,":");
            }
            lineaSplitMateria = strtok(NULL,",");
        }
    }
    fclose(fileBddMaterias);
    printf("BDD Materia cargada\n");
    ///bdd alumno
    printf("Cargando BDD Alumnos... \n");
    FILE* fileBddAlumno;
    fileBddAlumno = fopen("../bddAlumnos.txt", "r");
    char line[128] = {0};
    int lineaActual = 0 ;
    if(!fileBddAlumno){
        printf("no cargo la bdd llame a su tecnico mas cercano \n");
    }
    while (fgets(line, 128, fileBddAlumno)){
        lineaActual++;
        char* lineaSplit = strtok(line,",");
        char nombre[30];
        strcpy(nombre,lineaSplit);
        lineaSplit = strtok(NULL,",");
        int edad = atoi(lineaSplit);
        agregarAlumno(listaDeAlumnos,nombre,edad);
        /////// id de alumno es id de linea
        lineaSplit = strtok(NULL,",");
        if(lineaSplit != NULL) { /// aca cargamos todas las notas de alumno.
            char materia[250];
            char *puntero;
            strcpy(materia, lineaSplit);
            puntero = strtok(materia,"!:");
            while(puntero != NULL){
                int id = 0;
                int nota = 0;
                id = atoi(puntero);
                puntero = strtok(NULL,"!:");
                nota = atoi(puntero);
                cargarHistorialAlAlumno(listaMaterias,listaDeAlumnos,lineaActual,id,nota);
                puntero = strtok(NULL,"!:");
            }
        }
    }
    fclose(fileBddAlumno);
    printf("BDD Alumnos Cargada \n");
}
void guardarEnBdd(ListaMaterias* listaMaterias, ListaDeAlumnos* listaDeAlumnos){
    FILE* fileBddMateria;
    fileBddMateria = fopen("../bddMaterias.txt","w");
    Materia* materia = listaMaterias->cabeza;
    int lineaActual = 0;
    while(materia){
        lineaActual++;
        char correlativas[40] = {0};
        char lineaAEscribir[128]= {0};
        int tieneCorrelativas = 0;
        strcat(lineaAEscribir,materia->nombreMateria);
        for(int i = 0 ; i < 5 ; i++){
            if(materia->arrayCorrelativas[i]->idMateria != 0){
                if(i != 0){ strcat(correlativas,":");}
                char idmateria[10] = {0};
                itoa(materia->arrayCorrelativas[i]->idMateria,idmateria,10);
                strcat(correlativas,idmateria);
                tieneCorrelativas++;
            }
        }
        if(tieneCorrelativas != 0){
            strcat(lineaAEscribir,",");
            strcat(lineaAEscribir,correlativas);
        }else{
            strcat(lineaAEscribir,",0");
        }
        fprintf(fileBddMateria,"%s\n",lineaAEscribir);
        materia = materia->siguiente;
    }
    fclose(fileBddMateria);
    ///Guardar Alumnos
    FILE* fileBddAlumno;
    fileBddAlumno = fopen("../bddAlumnos.txt","w");
    Alumno* alumno = listaDeAlumnos->cabeza;
    if(!fileBddAlumno){
        printf("no cargo la bdd llame a su tecnico mas cercano \n");
    }
    lineaActual = 0;
    while(alumno){
        lineaActual++;
        char lineaAEscribir[128] = {0};
        strcpy(lineaAEscribir,alumno->Nombre);
        strcat(lineaAEscribir,",");
        char edad[3] = {0};
        itoa(alumno->edad,edad,10);
        strcat(lineaAEscribir,edad);
        HistorialDeLaMateria* historialDeLaMateria = alumno->listaDeHistorialDeMaterias->cabeza;
        while(historialDeLaMateria){
            char historialDeLaMateriaACargar[20] = {0};
            if(historialDeLaMateria == alumno->listaDeHistorialDeMaterias->cabeza){
                strcat(historialDeLaMateriaACargar,",");
            }else{
                strcat(historialDeLaMateriaACargar,":");
            }
            char idmateria[10];
            itoa(historialDeLaMateria->infoMateria->idMateria,idmateria,10);
            strcat(historialDeLaMateriaACargar,idmateria);
            strcat(historialDeLaMateriaACargar,"!");
            if(historialDeLaMateria->nota != NULL){
                char nota[2] = {0};
                itoa(historialDeLaMateria->nota,nota,10);
                strcat(historialDeLaMateriaACargar,nota);
            } else{
                strcat(historialDeLaMateriaACargar,"0");
            }
            strcat(lineaAEscribir,historialDeLaMateriaACargar);
            historialDeLaMateria = historialDeLaMateria->siguiente;
        }
        fprintf(fileBddAlumno,"%s\n",lineaAEscribir);
        alumno = alumno->siguiente;
    }
    fclose(fileBddAlumno);
}

/// Metodo ingresamos una array de chars y nos verifica si este mismo se puede transformar a integer return 0 si no puede y return 1 si puede;
int esUnInt(char integer[]){
    int valor = 0;
    valor = atoi(integer);
    if(valor == 0){
        return 0;
    }
    return 1;
}

///ESTE METEDO INDICA SI SE INGERSO UN NUMERO EN EL STRING, DEVUELVE 1 SI NO HAY NUMEROS
/// Y DEUVLE 0 SI HAY ALGUNO
int esUnChar(char character[]){
    int i;
    for (int j = 0; j < 30; j++) {
        i = atoi(&character[j]);
        if(i != 0) {
            return 0;
        }
        return 1;
    }

}
///TODO: TESTEAR AMBOS PAGINADOS
///TODO: PROBLEMA EN PRINTEO DE PAGINA MAX LO HACE MAL
void pagiandoDeAlumnos(ListaDeAlumnos* listaDeAlumnos){
    Alumno* alumnoPibote = listaDeAlumnos->cabeza;
    int paginaActual = 0;
    int cantidadAlumnosPorPagina = 0;
    printf("Ingrese Cantidad De Alumnos por pagina: \n");
    scanf("%i",&cantidadAlumnosPorPagina);
    if(cantidadAlumnosPorPagina<1){
        printf("El valor ingresado no es valido, se mostrarar por cantidad default, de 5 Materias por pagina \n");
        cantidadAlumnosPorPagina = 5;
    }
    int eleccionDePaginado = 1;
    do {
        alumnoPibote = getAlumno(listaDeAlumnos,(paginaActual*cantidadAlumnosPorPagina)+1);
        for(int i = paginaActual*cantidadAlumnosPorPagina;i < (paginaActual*cantidadAlumnosPorPagina)+cantidadAlumnosPorPagina;i++){
            if(alumnoPibote != NULL){
                printearAlumno(alumnoPibote);
            }
           if(alumnoPibote->siguiente != NULL){
               alumnoPibote = alumnoPibote->siguiente;
           } else{
               break;
           }
        }
        if(paginaActual != 0){ printf("1)pagina anterior");}
        printf("2)siguiente pagina 3)buscador de pagina 0)Salir ----pagina %i / %i ----\n",paginaActual+1,listaDeAlumnos->cantidadAlumnos/cantidadAlumnosPorPagina);
        scanf("%i",&eleccionDePaginado);
        if(paginaActual != 0 && eleccionDePaginado == 1){paginaActual--;}
        if(eleccionDePaginado == 2 && listaDeAlumnos->cantidadAlumnos > (paginaActual+1)*cantidadAlumnosPorPagina){;
            paginaActual++;
        }
        if(eleccionDePaginado == 3){
            printf("A que pagina desea ir? \n");
            scanf("%i",&paginaActual);
            paginaActual--;
            if(paginaActual < 0){
                printf("la pagina no puede ser negativa o 0\n");
            }
            if(listaDeAlumnos->cantidadAlumnos < (paginaActual)*cantidadAlumnosPorPagina){
                printf("no existe tal pagina , se volvera a la pagina 0 \n");
                paginaActual=0;
            }
        }
    }while(eleccionDePaginado != 0);
}

void pagiandoDeMaterias(ListaMaterias * listaDeMaterias){
    Materia* materiaPibote = listaDeMaterias->cabeza;
    int paginaActual = 0;
    int cantidadMateriasPorPagina = 0;
    printf("Ingrese Cantidad De Materias por pagina: \n");
    scanf("%i",&cantidadMateriasPorPagina);
    if(cantidadMateriasPorPagina<1){
        printf("El valor ingresado no es valido, se mostrarar por cantidad default, de 5 Materias por pagina \n");
        cantidadMateriasPorPagina = 5;
    }
    int eleccionDePaginado = 1;
    do {
        materiaPibote = getMateria(listaDeMaterias, (paginaActual * cantidadMateriasPorPagina) + 1);
        for(int i = paginaActual * cantidadMateriasPorPagina; i < (paginaActual * cantidadMateriasPorPagina) + cantidadMateriasPorPagina; i++){
            if(materiaPibote != NULL){
                printearMateria(listaDeMaterias,materiaPibote->idMateria);///TODO: DEJAR ASI O CAMBIAR METODO PARA SOLO PASARLE LA MATERIA;
            }
            if(materiaPibote->siguiente != NULL){
                materiaPibote = materiaPibote->siguiente;
            } else{
                break;
            }
        }
        if(paginaActual != 0){ printf("1)pagina anterior");}
        printf("2)siguiente pagina 3)buscador de pagina 0)Salir ----pagina %i / %i ----\n",paginaActual+1, listaDeMaterias->cantidadMaterias / cantidadMateriasPorPagina);
        scanf("%i",&eleccionDePaginado);
        if(paginaActual != 0 && eleccionDePaginado == 1){paginaActual--;}
        if(eleccionDePaginado == 2 && listaDeMaterias->cantidadMaterias > (paginaActual + 1) * cantidadMateriasPorPagina){;
            paginaActual++;
        }
        if(eleccionDePaginado == 3){
            printf("A que pagina desea ir? \n");
            scanf("%i",&paginaActual);
            paginaActual--;
            if(paginaActual < 0){
                printf("la pagina no puede ser negativa o 0\n");
            }
            if(listaDeMaterias->cantidadMaterias < (paginaActual) * cantidadMateriasPorPagina){
                printf("no existe tal pagina , se volvera a la pagina 0 \n");
                paginaActual=0;
            }
        }
    }while(eleccionDePaginado != 0);
}

//si returnea -1 quiere decir que algun error ocurrio;
int verificadorDeValorIngresado( char valorIngresado[] ) {
    int valorFinal = -1;
    if(esUnInt(valorIngresado) == 1){
        int validador = atoi(valorIngresado);
        if(validador > 0){
            valorFinal = validador;
        }
    }
    return valorFinal;
}

int ingresarInteger(){
    char ingresado[] = {0};
    scanf(" %s",&ingresado);
    return verificadorDeValorIngresado(ingresado);
}
