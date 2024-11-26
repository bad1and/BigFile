#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h> // Для gettimeofday


int count_min = 0;
int count_max = 0;

// подсчет букв
void count_letters_in_line(const char *line) {
    for (int i = 0; i < strlen(line); i++) {
        if (line[i] == 'o') {
            count_min++;
        } else if (line[i] == 'O') {
            count_max++;
        }
    }
}

// открытие файла
void process_file(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Unable to open file");
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; //символ \n
        count_letters_in_line(line);
    }

    fclose(file);
}

// время
double measure_time(void (*function)(const char *), const char *file_path) {
    struct timeval start, end;
    gettimeofday(&start, NULL);

    function(file_path);

    gettimeofday(&end, NULL);
    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
}

// Основная функция
int main() {
    const char *file_path = "words.txt";

    double elapsed_time = measure_time(process_file, file_path);

    printf("Больших букв O: %d\n", count_max);
    printf("Маленьких букв o: %d\n", count_min);
    printf("Время выполнения: %.6f секунд\n", elapsed_time);

    return 0;
}
