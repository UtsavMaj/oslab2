#include <stdio.h> 
#include <unistd.h> // For fork, getpid, and getppid
#include <sys/wait.h> // For wait()

int main() 
{ 
    // Create a child process using fork
    int pid = fork(); 
    
    if (pid == 0) // Child process
    { 
        // Print details from the child process
        printf("In Child Process\n");
        printf("Parent Process ID: %d\n", getppid()); // Parent process ID
        printf("Child Process ID: %d\n", getpid()); // Child process ID
    } 
    else if (pid > 0) // Parent process
    { 
        // Wait for the child to complete
        wait(NULL); 

        // Print details from the parent process
        printf("In Parent Process\n");
        printf("Parent Process ID: %d\n", getpid()); // Parent process ID
        printf("Child Process ID: %d\n", pid); // Child process ID (returned by fork)
    } 
    else 
    { 
        // If fork() fails
        printf("Fork failed.\n");
        return 1;
    }

    return 0; 
}
