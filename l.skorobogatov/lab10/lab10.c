#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int status;
int main(int argc, char* argv[])
{
    

    pid_t sub_proc = fork();
    if (sub_proc == -1)
    {
        perror("Failed sub-processing");
        _exit(1);
    }
    char * path = malloc(sizeof(char)*(strlen(argv[1]) + 11));
    strcpy(path, "/bin/");
    strcat(path, argv[1]);

    if (sub_proc == 0)       
    {
        execv(path, &argv[1]);
        exit(errno);
    }
   
        if (waitpid(sub_proc, &status, WUNTRACED) != sub_proc)      
        {
            exit(7);
        }
        else
        {
            printf(" status: %d\n", WEXITSTATUS(status));
        }
    }
   return 0;
}
