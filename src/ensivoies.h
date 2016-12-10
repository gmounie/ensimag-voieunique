#ifndef ENSIVOIES_H
#define ENSIVOIES_H

#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>

enum SENS { EO, OE };

struct Trajet {
    int numero;
    int heure_depart;
    enum SENS sens;
    int duree_trajet;
};

extern useconds_t DELAI;

#define handle_fatalError(msg,fname)					\
    do { char c[512] = {}; snprintf(c, 511, "%s %s",msg, fname);	\
	perror(c); exit(EXIT_FAILURE); } while(0)

#endif

