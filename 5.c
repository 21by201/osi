#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
 
int global_variable = 10;
 
void print_variable(char* name, int* variable) {
    printf("%s - Address: %p, Value: %d\n", name, variable, *variable);
}
 
int main() {
    int local_variable = 20;
 
    printf("Global Variable:\n");
    print_variable("Global", &global_variable);
 
    printf("\nLocal Variable:\n");
    print_variable("Local", &local_variable);
 
    printf("\nPID: %d\n", getpid());
 
    pid_t pid = fork();
 
    if (pid == -1) {
        printf("Error creating child process.\n");
        exit(1);
    } else if (pid == 0) {
        printf("\nChild Process:\n");
        printf("PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
 
        printf("\nVariables in Child Process:\n");
        print_variable("Global", &global_variable);
        print_variable("Local", &local_variable);
 
        global_variable = 30;
        local_variable = 40;
 
        printf("\nChanged Variables in Child Process:\n");
        print_variable("Global", &global_variable);
        print_variable("Local", &local_variable);
 
        exit(5);
    } else {
        printf("\nParent Process:\n");
        printf("PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
 
        int status;
        waitpid(pid, &status, 0);
 
        if (WIFEXITED(status)) {
            printf("\nChild Process Terminated Normally.\n");
            printf("Exit Status: %d\n", WEXITSTATUS(status));
        } else {
            printf("\nChild Process Terminated Abnormally.\n");
            printf("Exit Status: N/A\n");
        }
 
        printf("\nVariables in Parent Process:\n");
        print_variable("Global", &global_variable);
        print_variable("Local", &local_variable);
 
        sleep(10);
    }
 
    return 0;
}