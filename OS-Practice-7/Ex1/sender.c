// sender.c

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
        printf("Received signal from receiver. Sending data...\n");

        // Prompt user for input
        printf("Enter the number of integers: ");
        int n;
        scanf("%d", &n);

        // Store user input in shared memory
        for (int i = 0; i < n; ++i) {
            printf("Enter integer %d: ", i + 1);
            scanf("%d", &shm_ptr[i]);
        }

        // Send signal to receiver that data is ready
        kill(getpid() + 1, SIGUSR1);

        // Wait for receiver to finish calculations
        pause();

        // Print the calculated sum
        printf("Sum received from receiver: %d\n", shm_ptr[0]);
    }
}

int main() {
    // Attach to shared memory
    shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    shm_ptr = (int*)shmat(shmid, NULL, 0);

    // Set up signal handler
    signal(SIGUSR1, handle_signal);

    printf("Sender process started. Waiting for signal...\n");

    // Send initial signal to receiver
    kill(getpid() + 1, SIGUSR1);

    // Wait for receiver to finish
    pause();

    // Detach from shared memory
    shmdt(shm_ptr);

    // Remove shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

