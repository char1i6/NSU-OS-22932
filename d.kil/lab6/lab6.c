#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

#define MAX_LINE_LENGTH 100

struct LineInfo {
    off_t offset;
    int length;
};

void display(int fd, struct LineInfo* lines, int line_count) {
    char buffer[MAX_LINE_LENGTH];
    for (int i = 0; i < line_count; i++) {
        lseek(fd, lines[i].offset, SEEK_SET);
        read(fd, buffer, lines[i].length);
        buffer[lines[i].length] = '\0';
        printf("%s\n", buffer);
    }
}

int main() {
    char filename[100];
    printf("Enter file name: ");
    scanf("%s", filename);
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("File opening error");
        exit(1);
    }
    struct LineInfo lines[MAX_LINE_LENGTH];
    char buffer[MAX_LINE_LENGTH];
    int line_count = 0;
    while (read(fd, buffer, 1) > 0) {
        lines[line_count].offset = lseek(fd, 0L, SEEK_CUR) - 1;
        if (buffer[0] == '\n') {
            lines[line_count].length = lseek(fd, 0L, SEEK_CUR) - lines[line_count].offset - 1;
            line_count++;
        }
    }
    char input[10];
    int line_number;
    struct timeval start_time, current_time, elapsed_time;
    gettimeofday(&start_time, NULL);
    while (1) {
        printf("Enter line number (0 to exit): ");
        gettimeofday(&current_time, NULL);
        timersub(&current_time, &start_time, &elapsed_time);
        if (elapsed_time.tv_sec >= 5) {
            printf("Time is up. Outputting the contents of the file:\n");
            display(fd, lines, line_count);
            break;
        }
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Input enter\n");
            continue;
        }
        if (sscanf(input, "%d", &line_number) != 1) {
            printf("Invalid enter\n");
            continue;
        }

        if (line_number == 0) {
            break;
        }

        if (line_number < 0 || line_number > line_count) {
            printf("Invalid line number\n");
            continue;
        }

        lseek(fd, lines[line_number - 1].offset, SEEK_SET);
        read(fd, buffer, lines[line_number - 1].length);
        buffer[lines[line_number - 1].length] = '\0';

        printf("%s\n", buffer);
    }
    close(fd);
    return 0;
}