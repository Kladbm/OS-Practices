// receiver.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int shmid;
int *shm_ptr;

void handle_signal(int signum) {
    // Signal handler for SIGUSR1
    if (signum == SIGUSR1) {
        printf("Received signal from sender. Calculating sum...\n");

        // Calculate sum
        int sum = 0;
        for (int i = 0; i < SHM_SIZE / sizeof(int); ++i) {
            sum += shm_ptr[i];
        }

        // Store the sum in shared memory
        shm_ptr[0] = sum;

        // Send signal to sender that calculation is done
        kill(getppid(), SIGUSR1);
    }
}

int main() {
    // Attach to shared memory
    shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    shm_ptr = (int*)shmat(shmid, NULL, 0);

    // Set up signal handler
    signal(SIGUSR1, handle_signal);

    printf("Receiver process started. Waiting for data...\n");

    while (1) {
        // Wait for data input signal from sender
        pause();
    }

    // Detach from shared memory
    shmdt(shm_ptr);

    return 0;
}

