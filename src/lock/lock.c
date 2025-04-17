#include "lock.h"

#include <stdio.h>

void amountInit(lock_t* Account) {
    // Account->amount = 0;
    // pthread_mutex_init(&Account->mutex, NULL);

}

void Income(lock_t* Account, int amount) {
    if(pthread_mutex_trylock(&Account->mutex) == 0)
    {
        Account->amount += amount;

        pthread_mutex_unlock(&Account->mutex);
    }
    else
    {
        pthread_mutex_lock(&Account->mutex);
        Account->amount += amount;
        pthread_mutex_unlock(&Account->mutex);
    }
}

void Expend(lock_t* Account, int amount) {
    if(pthread_mutex_trylock(&Account->mutex) == 0)
    {
        Account->amount -= amount;
        pthread_mutex_unlock(&Account->mutex);
    }
    else
    {
        pthread_mutex_lock(&Account->mutex);

        Account->amount -= amount;
        pthread_mutex_unlock(&Account->mutex);
    }
}
