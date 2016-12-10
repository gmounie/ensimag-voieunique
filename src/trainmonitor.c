#include <pthread.h>
#include "train.h"
#include "ensivoies.h"
#include "trainmonitor.h"

// Ajouter votre code ici
static pthread_mutex_t m= PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cOE= PTHREAD_COND_INITIALIZER;
static pthread_cond_t cEO= PTHREAD_COND_INITIALIZER;
static int sens= -1;
static int nb= 0;

void initThreadSynchro() {
    // Ajouter votre code ici
};

pthread_t AllumageTrain(void *arg) {
    // Ajouter votre code ici
    pthread_t th;   
    int res= pthread_create(& th, 0, train, arg);
    if (res)
	handle_fatalError("create", __FILE__);
    return th;
}
void TerminaisonTrain(pthread_t t) {
    // Ajouter votre code ici
    int res = pthread_join(t, NULL);
    if (res)
	handle_fatalError("join", __FILE__);
    
};

// Est-Ouest
void entreeEO() {
    pthread_mutex_lock(& m);
    while(sens == OE && nb > 0)
	pthread_cond_wait(&cEO, &m);

    if (sens != EO) {
	sens = EO;
	pthread_cond_broadcast(& cEO);
    }
    nb ++;
    pthread_mutex_unlock(& m);
}

void sortieEO() {
    pthread_mutex_lock(& m);
    nb --;
    if (nb == 0)
	pthread_cond_signal(& cOE);
    
    pthread_mutex_unlock(& m);
}

// Ouest-Est
void entreeOE() {
    pthread_mutex_lock(& m);
    while(sens == EO && nb > 0)
	pthread_cond_wait(&cOE, &m);

    if (sens != OE) {
	sens = OE;
	pthread_cond_broadcast(& cOE);
    }
    nb ++;
    pthread_mutex_unlock(& m);
}

void sortieOE() {
    pthread_mutex_lock(& m);
    nb --;
    if (nb == 0)
	pthread_cond_signal(& cEO);
    pthread_mutex_unlock(& m);
}

