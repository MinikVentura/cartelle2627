#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define gente 20
#define PARTIDOS_EQUIPO 1
char criterioOrden[20];
typedef enum { minutos, partidos, titularidades, goles, minP, amarillas} Criterio;

/*COPA 1*/
const char *titularesC1[] = {"Conde", "Vasco", "Izan","Jose", "Samu", "Brian", "Noel", "Duque", "David", "Nunez", "Bacelar"};
const char *suplentesC1[] = {"Gus", "Juvenil", "Yago", "Brais", "Rodrigo", "Raul", "Seara"};
const char *cambiadosC1[] = {"Nunez", "Vasco", "Bacelar", "Brian", "Rodrigo", "Raul", "Seara"};
const char *golesC1[] = {""};
const char *amarillasC1[] = {"Duque", "Brais"};
int cambiosC1[7] = {45, 45, 62, 75, 90, 90, 90};

typedef struct {
    char *nombre;
    int minutos;
    int partidos;
    int titularidades;
    int goles;
    int minP;
    int amarillas;
    int rojas;
    int porcentaje;
}jugador;

jugador *lJugador[gente];

void crearJugadores(const char *jugadores[]){
    int i=0;

    for (i = 0; i < gente; i++){

        lJugador[i] = malloc(sizeof(jugador));
        if (lJugador[i] == NULL){
            printf("Error al reservar memoria\n");
            exit(1);
        }

        lJugador[i]->nombre = malloc(strlen(jugadores[i]) + 1);
        if (lJugador[i]->nombre == NULL) {
            printf("Error al reservar memoria para nombre\n");
            exit(1);
        }

        strcpy(lJugador[i]->nombre, jugadores[i]);
        lJugador[i]->minutos = 0;
        lJugador[i]->partidos = 0;
        lJugador[i]->titularidades = 0;
        lJugador[i]->goles = 0;
        lJugador[i]->minP = 0;
        lJugador[i]->amarillas = 0;
        lJugador[i]->rojas = 0;
        lJugador[i]->porcentaje = 0;
    }
}


void printJugadores(void) {
    printf("\n");
    printf("Estadisticas de Jugadores - Total %d jugadores  || Ordenado por %s\n", gente, criterioOrden);
    printf("--------------------------------------------------------------------------------------------\n");
    printf(" #  Nombre       PJ  Tit   Minutos  Goles   TA   TR   Min/PJ   %%Min\n");
    printf("--------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < gente; i++) {
        jugador *j = lJugador[i];

        // Alineación cuidada:
        // - Nombre: 12 caracteres (izquierda)
        // - Números enteros con ancho fijo y alineados a la derecha
        printf("%2d  %-12s %2d  %3d    %4d    %3d    %2d   %2d    %3d  \t%2d%%\n",
               i + 1,
               j->nombre,
               j->partidos,
               j->titularidades,
               j->minutos,
               j->goles,
               j->amarillas,
               j->rojas,
               j->partidos > 0 ? (j->minutos / j->partidos) : 0,
               j->porcentaje
        );
    }

    printf("--------------------------------------------------------------------------------------------\n");
    printf("\n");
}

void jornada(const char *titulares[], const char *suplentes[], const char *goles[], int numGoles, int cambios[], const char *cambiados[], const char *amarillas[], int numAmarillas, int numSuplentes, int numJornada){

  int numTitulares = 11;

  for (int i = 0; i < numTitulares; i++) {
        for (int j = 0; j < gente; j++) {

            if (strcmp(lJugador[j]->nombre, titulares[i]) == 0) {
                lJugador[j]->minutos += 90;
                for (int m = 0; m < numSuplentes; m++) {
                  if (strcmp(lJugador[j]->nombre, cambiados[m]) == 0){
                    lJugador[j]->minutos -= (90 -cambios[m]);
                  }
                }
                lJugador[j]->partidos += 1;
                lJugador[j]->titularidades += 1;
                for (int k = 0; k < numGoles; k++){
                  if(strcmp(lJugador[j]->nombre, goles[k]) == 0)lJugador[j]->goles += 1;
                }
                for (int a = 0; a < numAmarillas; a++){
                  if(strcmp(lJugador[j]->nombre, amarillas[a]) == 0)lJugador[j]->amarillas += 1;
                }
                lJugador[j]->minP = lJugador[j]->minutos/lJugador[j]->partidos;
                break;
            }
        }
   }

   for (int i = 0; i < numSuplentes; i++) {
        for (int j = 0; j < gente; j++) {

            if (strcmp(lJugador[j]->nombre, suplentes[i]) == 0) {
                lJugador[j]->minutos += 90-cambios[i];
                lJugador[j]->partidos += 1;
                lJugador[j]->titularidades += 0;
                for (int k = 0; k < numGoles; k++){
                  if(strcmp(lJugador[j]->nombre, goles[k]) == 0)lJugador[j]->goles += 1;
                }
                for (int a = 0; a < numAmarillas; a++){
                  if(strcmp(lJugador[j]->nombre, amarillas[a]) == 0)lJugador[j]->amarillas += 1;
                }
                lJugador[j]->minP = lJugador[j]->minutos/lJugador[j]->partidos;
                break;
            }
        }
   }
}

int comparar(const void *a, const void *b) {
    jugador *j1 = *(jugador **)a;
    jugador *j2 = *(jugador **)b;

    if (strcmp(criterioOrden, "minutos") == 0) {
        return j2->minutos - j1->minutos;
    }
    else if (strcmp(criterioOrden, "partidos") == 0) {
        return j2->partidos - j1->partidos;
    }
    else if (strcmp(criterioOrden, "titularidades") == 0) {
        return j2->titularidades - j1->titularidades;
    }
    else if (strcmp(criterioOrden, "goles") == 0) {
        return j2->goles - j1->goles;
    }
    else if (strcmp(criterioOrden, "minP") == 0) {
        return j2->minP - j1->minP;
    }
    else if (strcmp(criterioOrden, "amarillas") == 0) {
        return j2->amarillas - j1->amarillas;
    }
    else if (strcmp(criterioOrden, "rojas") == 0) {
        return j2->rojas - j1->rojas;
    }
    else if (strcmp(criterioOrden, "porcentaje") == 0) {
        return j2->porcentaje - j1->porcentaje;
    }

    return 0;
}

void ordenar(const char *criterio) {
    strcpy(criterioOrden, criterio);
    qsort(lJugador, gente, sizeof(jugador*), comparar);
}

void anomalias(){
  for (int j = 0; j < gente; j++) {
    if (strcmp(lJugador[j]->nombre, "Villa") == 0){ //expulsion vs Peroxa
      lJugador[j]->minutos -= 47;
      lJugador[j]->minP = lJugador[j]->minutos /lJugador[j]->partidos;
      lJugador[j]->rojas += 1;
    }
  }
}

void calcularPorcentajes(void) {
    int minutos_totales_posibles = PARTIDOS_EQUIPO * 90;

    for (int i = 0; i < gente; i++) {
        if (minutos_totales_posibles > 0) {
            lJugador[i]->porcentaje =
                (lJugador[i]->minutos * 100LL) / minutos_totales_posibles;
            // Usamos 100LL para evitar overflow y truncamiento prematuro
            if(lJugador[i]->porcentaje == 0) lJugador[i]->porcentaje = 1;
        } else {
            lJugador[i]->porcentaje = 0;
        }
    }
}

int main(){
    const char *nombres[] = {"Conde", "Samu", "Rodrigo", "Vasco", "Izan", "David", "Bacelar", "Duque", "Brais", "Yago", "Villa", "Jose", "Brian", "Raul", "Juvenil", "Noel", "Seara", "Requejo", "Nunez", "Gus"};
    crearJugadores(nombres);
    jornada(titularesC1, suplentesC1, golesC1, 0, cambiosC1, cambiadosC1, amarillasC1, 2, 7, 1);
    //anomalias();
    calcularPorcentajes();
    ordenar("minutos");
    printJugadores();

    return 0;
}