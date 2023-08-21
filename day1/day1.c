#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void rm_newline(char* line)
{
    while (line != 0) {
        if (*line == '\r' || *line == '\n') {
            *line = 0;
            return;
        }
        line++;
    }
}

int line_to_int(char* line)
{
    long int value = 0;
    while (*line != 0) {
        if (*line < '0' || *line > '9') return -1; // invalid char
        value = value*10 + *line - '0';
        line++;
    }
    return value;
}

int main(int argc, char** argv)
{
    FILE* fd_input;
    char buff[32];
    int aux;
    unsigned int most_calories[3] = {0};
    unsigned int curr_calories;

    if (argc != 2) {
        printf("Bad usage. Pass input file as argument, eg: %s <input.txt>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((fd_input = fopen(argv[1], "r")) == NULL) {
        printf("Unable to open %s in read mode. Verify path of file.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    curr_calories = 0;
    while (fgets(buff, 32, fd_input)) {
        printf(">>> %s", buff);
        rm_newline(buff);
        if (*buff == 0) {
            printf("will reset calories | curr counter :: %u\n", curr_calories);
            if (curr_calories > most_calories[0]) {
                aux = most_calories[0];
                most_calories[0] = curr_calories;
                curr_calories = aux;
            }
            if (curr_calories > most_calories[1]) {
                aux = most_calories[1];
                most_calories[1] = curr_calories;
                curr_calories = aux;
            }
            if (curr_calories > most_calories[2]) {
                most_calories[2] = curr_calories;
            }
            curr_calories = 0;
            continue;
        }

        aux = line_to_int(buff);
        if (aux < 0) {
            printf("invalid data: %s\n", buff);
            break;
        }

        curr_calories += aux;
        printf("current counter of calories :: %u\n", curr_calories);
    }

    fclose(fd_input);

    printf("most calories :: %u\n", most_calories[0]+most_calories[1]+most_calories[2]);
    return 0;
}