#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void print_george() {
    while (1) {
        printf("George\n");
        sleep(1);
    }
}

void print_mary() {
    while (1) {
        printf("Mary\n");
        sleep(2);
    }
}

void print_separator() {
    while (1) {
        printf("----------------\n");
        sleep(1);
    }
}

int main() {
    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 < 0) {
        perror("fork failed");
        exit(1);
    }
    if (pid1 == 0) {
        // First child process
        print_george();
        exit(0);
    }

    pid2 = fork();
    if (pid2 < 0) {
        perror("fork failed");
        exit(1);
    }
    if (pid2 == 0) {
        // Second child process
        print_mary();
        exit(0);
    }

    // Parent process
    print_separator();

    // Wait for child processes to finish (they won't, as they're infinite loops)
    wait(NULL);
    wait(NULL);

    return 0;
}
