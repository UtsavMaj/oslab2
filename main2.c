#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h> // For exit()

int main() 
{ 
    int a = 5, b = 10, pid; 
    printf("Before vfork a=%d b=%d \n", a, b); 
    
    pid = vfork(); 
    if (pid == 0) 
    { 
        a = a + 1; 
        b = b + 1; 
        printf("In child a=%d b=%d \n", a, b); 
        _exit(0); // Use _exit() after vfork to avoid affecting parent
    } 
    else // Parent process
    { 
        sleep(1); // Wait for child to complete execution
        a = a - 1; 
        b = b - 1; 
        printf("In Parent a=%d b=%d \n", a, b); 
    } 
    
    return 0; 
}
