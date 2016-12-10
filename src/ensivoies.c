#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <assert.h>

// pthread
#include <pthread.h>

// for exit
#include <unistd.h>

// for stat
#include <sys/stat.h>

// for dir traversal
#include <sys/types.h>
#include <dirent.h>

// headers of this file
#include "ensivoies.h"
// headers of the monitor
#include "trainmonitor.h"

// error macro
#define concat(msg, fname) # msg fname

#define handle_fatalError(msg,fname)					\
    do { char c[512] = {}; snprintf(c, 511, "%s %s",msg, fname);	\
	perror(c); exit(EXIT_FAILURE); } while(0)

// global variable
bool verbose = false;

// nb of threads
static int SCENARIO= 0;
useconds_t DELAI= 200000; // ms granularity applied to scenario

struct Trajet s0[] = { {1, 0, OE, 1}, {0}};
struct Trajet s1[] = { {1, 0, OE, 2},
		       {2, 0, OE, 2},
		       {3, 0, OE, 2},
		       {4, 0, OE, 2},
		       {5, 1, OE, 2}, {0} };
struct Trajet s2[] = { {1, 0, OE, 2},
		       {2, 1, EO, 2},
		       {3, 0, OE, 2}, {0}};
struct Trajet s3[] = { {1, 0, OE, 2},
		       {2, 0, OE, 1},
		       {3, 0, OE, 2},
		       {4, 0, OE, 1}, {0} };
struct Trajet s4[] = { {1, 0, OE, 2},
		       {2, 0, OE, 2},
		       {3, 0, OE, 2},
		       {4, 1, EO, 2},
		       {5, 1, EO, 2},
		       {6, 1, EO, 2}, {0} };



void joueScenario() {
    int nbtrains=0;
    struct Trajet *scenario[]= { s0, s1, s2, s3, s4, 0};
    assert(SCENARIO < 5);
    
    while(scenario[SCENARIO][nbtrains].numero != 0)
	nbtrains++;

    pthread_t *th = calloc(nbtrains, sizeof(pthread_t));
    for(int i=0; i < nbtrains; i++)
	th[i] = AllumageTrain( (void *)& scenario[SCENARIO][i] );

    
    for(int i=0; i < nbtrains; i++)
	TerminaisonTrain( th[i] );
    
}


/**
   The program start scenari of different train problems 
*/

int main(int argc, char **argv) {
    while(1) {
	int option_index;
	struct option long_options[] = {
	    {"verbose", no_argument, 0, 'v'},
	    {"scenario", required_argument, 0, 's'},
	    {"delai", required_argument, 0, 'd'},
	    {0, 0, 0, 0}
	};
	int c = getopt_long(argc, argv, "vd:s:",
			    long_options, &option_index);
	if (c == -1)
	    break;

	switch(c) {
	case 'v':
	    verbose = true;
	    break;
	case 's':
	    if (optarg)
		SCENARIO = atoi(optarg);
	    break;
	case 'd':
	    if (optarg)
		DELAI = atoi(optarg);	    
	    break;
	default:
	    fprintf(stderr,
		    "Usage: %s [-s] [-v] [-s SCENARIO]\n", argv[0]);
	    exit(EXIT_FAILURE);
	}
    }

    initThreadSynchro();
    joueScenario();
    printf("The End\n");
    return 0;
}
