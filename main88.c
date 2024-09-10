#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int pid, semid;
    struct sembuf sop;

    // Create a semaphore with a unique key (key_t 6) and one semaphore
    semid = semget((key_t)6, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget failed");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    sop.sem_num = 0;  // semaphore index 0
    sop.sem_op = 0;   // wait operation (wait for semaphore value to become 0)
    sop.sem_flg = 0;  // no special flags

    if (pid != 0) // Parent process
    {
        sleep(1);
        printf("The Parent waits for WAIT signal\n");
        semop(semid, &sop, 1); // Wait for the semaphore to become 0
        printf("The Parent WAKED UP & doing her job\n");
        sleep(10);
        printf("Parent Over\n");
    }
    else // Child process
    {
        printf("The Child sets WAIT signal & doing her job\n");
        semctl(semid, 0, SETVAL, 1); // Set semaphore value to 1 (signal)
        sleep(10);
        printf("The Child sets WAKE signal & finished her job\n");
        semctl(semid, 0, SETVAL, 0); // Set semaphore value to 0 (wake up parent)
        printf("Child Over\n");
    }

    return 0;
}
