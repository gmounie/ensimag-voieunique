#ifndef TRAINMONITOR_H
#define TRAINMONITOR_H

#include <pthread.h>

void initThreadSynchro();

pthread_t AllumageTrain(void *arg);
void TerminaisonTrain(pthread_t t);

// Est-Ouest
void entreeEO();
void sortieEO();

// Ouest-Est
void entreeOE();
void sortieOE();

#endif
