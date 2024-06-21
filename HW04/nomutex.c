#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 10
#define NUM_OPERATIONS 100000

int balance = 0;

void* deposit(void* arg) {
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        int temp = balance;
        temp += 1;
        balance = temp;
        // 检查余额
        if (balance != temp) {
            printf("Error in deposit: expected balance %d, got %d\n", temp, balance);
        }
    }
    return NULL;
}

void* withdraw(void* arg) {
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        int temp = balance;
        temp -= 1;
        balance = temp;
        // 检查余额
        if (balance != temp) {
            printf("Error in withdraw: expected balance %d, got %d\n", temp, balance);
        }
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Create deposit threads
    for (int i = 0; i < NUM_THREADS / 2; ++i) {
        pthread_create(&threads[i], NULL, deposit, NULL);
    }

    // Create withdraw threads
    for (int i = NUM_THREADS / 2; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, withdraw, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("Final balance (without mutex): %d\n", balance);

    return 0;
}
