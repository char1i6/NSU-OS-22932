#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct Line {
    off_t offset;
    off_t length;
}Line;

typedef struct List {
    Line* array;
    int cnt;
    int cap;
}List;

void initArray(List* a) {
    a->array = (Line*)malloc(sizeof(Line));
    a->cnt = 0;
    a->cap = 1;
}

void insertArray(List* a, Line element) {
    if (a->cnt == a->cap) {
        a->cap *= 2;
        a->array = realloc(a->array, a->cap * sizeof(Line));
    }

    a->array[a->cnt++] = element;
}

void freeArray(List* a) {
    free(a->array);
    a->array = NULL;
    a->cnt = a->cap = 0;
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
    }
    else
    {
        return 1;
    }
    char* path = argv[1];

    List arr;
    initArray(&arr);

    int fd = open(path, O_RDONLY);
    if (fd == -1) { return 1; }
    lseek(fd, 0L, SEEK_CUR);

    char c;
    off_t lineOffset = 0;
    off_t lineLength = 0;
    while (read(fd, &c, 1) == 1) {
        if (c != '\n') {
            lineLength++;
        }
        if (c == '\n') {
            Line current = { lineOffset, lineLength };
            insertArray(&arr, current);

            lineOffset += lineLength + 1;
            lineLength = 0;

        }
    }

    if (lineLength > 0) {
        Line current = { lineOffset, lineLength };
        insertArray(&arr, current);
    }
    int num = -1;
    while (num != 0) {

        printf("Enter the line number: ");
        scanf("%d", &num);


        if (arr.cnt < num) {
            printf("The file contains only %d line(s).\n", arr.cnt);
            continue;
        }

        Line line = arr.array[num - 1];
        char* buf = calloc(line.length + 1, sizeof(char));

        lseek(fd, line.offset, SEEK_SET);
        read(fd, buf, line.length * sizeof(char));

        printf("%s\n", buf);
        free(buf);
    }

    

    return 0;
}