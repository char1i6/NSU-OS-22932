#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int flag1 = 0, flag2 = 0, status, neg_one = -1;
int main() {
    pid_t children;

 
    if ((children = fork()) == neg_one) {
        perror("Error");
        exit(EXIT_FAILURE);
    }

    if (children == 0) {
        
        execlp("cat", "cat", "longfile.txt", NULL);
        perror("Error executing cat");
        exit(EXIT_FAILURE);
    } 
    
        
        printf("Parent process before waiting:\n");

        
        waitpid(children, &status, 0);
        
        if (WIFEXITED(status)) {
            printf("Status: %d\n", WEXITSTATUS(status));
            flag1 = 1;
        }  
        if (WIFSIGNALED(status)) {
            printf("Status %d\n", WTERMSIG(status));
            flag2 = 1;
        } 
        if (flag1 + flag2 == 0){
            printf("Error of proccess.\n");
        }
    

    return 0;
}
