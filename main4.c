#include <stdio.h> 
#include <unistd.h> 
#include <sys/wait.h> // For wait()

int main() 
{ 
    int pid, n, oddsum = 0, evensum = 0; 
    
    // Input the value of n
    printf("Enter the value of n: "); 
    scanf("%d", &n); 
    
    // Create a child process using fork
    pid = fork(); 
    
    if (pid == 0) // Child process
    { 
        // Calculate sum of odd numbers
        for (int i = 1; i <= n; i++) 
        {
            if (i % 2 != 0) // Odd number
                oddsum += i;
        }
        printf("Child: Sum of odd numbers up to %d is %d\n", n, oddsum); 
    } 
    else // Parent process
    { 
        // Wait for the child process to finish
        wait(NULL);
        
        // Calculate sum of even numbers
        for (int i = 1; i <= n; i++) 
        {
            if (i % 2 == 0) // Even number
                evensum += i;
        }
        printf("Parent: Sum of even numbers up to %d is %d\n", n, evensum); 
    }
    
    return 0; 
}
