#include <stdio.h>
#include <assert.h>
#include "ensivoies.h"
#include "trainmonitor.h"

void (*entrees[2])()= { entreeEO, entreeOE };
void (*sorties[2])()= { sortieEO, sortieOE };

void *train(void *arg) {
    struct Trajet *trajet= (struct Trajet *) arg;

    if (trajet->sens != OE && trajet->sens != EO ) {
    	fprintf(stderr, "BUG: Incohérence dans le sens (valeur %d au lieu de %d ou %d)\n",
	       trajet->sens, OE, EO);
	assert(0);
    }

    usleep(trajet->heure_depart * DELAI);
    printf("Train %d: depart a %d us\n", trajet->numero,
	trajet->heure_depart * DELAI);

    if (trajet->sens == EO)
	entreeEO();
    else
	entreeOE();

    printf("Train %d: voie unique, sens %d pendant %d us\n", trajet->numero,
	   trajet->sens, trajet->duree_trajet*DELAI);
    usleep(trajet->duree_trajet * DELAI);
    
    if (trajet->sens == EO)
	sortieEO();
    else
	sortieEO();
    
    printf("Train %d: sortie, sens %d\n", trajet->numero,
	   trajet->sens);

    return 0;
}
