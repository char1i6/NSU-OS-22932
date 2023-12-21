#include <signal.h>
#include <stdlib.h>
#include <stdio.h>


unsigned int counter = 0;
char value;
void make_signal(int) {
    printf("\007");
    counter++;

    return;
}

void stop(int) {
    printf("It was %u beeps", counter);
    return 0;
}

int main() {
    signal(SIGINT, make_signal);
    signal(SIGQUIT, stop);
    
    while (1)
    {
        scanf("%c", &value);
    }
    return 0;
}