#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

// Подсчёт букв
void count_letters_in_line(const char line[], int *count_o, int *count_O) {
    *count_o = 0;
    *count_O = 0;

    for (int i = 0; i < strlen(line); i++) {
        if (line[i] == 'o') {
            (*count_o)++;
        } else if (line[i] == 'O') {
            (*count_O)++;
        }
    }
}

// Открытие файла
void process_file(const char input_path[], const char output_path[]) {
    FILE *input_file = fopen(input_path, "r");
    if (input_file == NULL) {
        perror("Unable to open input file");
        exit(1);
    }

    FILE *output_file = fopen(output_path, "w");
    if (output_file == NULL) {
        perror("Unable to open output file");
        fclose(input_file);
        exit(1);
    }

    int line_number = 0;
    int total_o = 0;
    int total_O = 0;

    char line[256];

    while (fgets(line, sizeof(line), input_file)) {
        line_number++;
        line[strcspn(line, "\n")] = 0;

        int count_o = 0;
        int count_O = 0;
        count_letters_in_line(line, &count_o, &count_O);

        fprintf(output_file, "Строка %d: Маленьких 'o': %d, Больших 'O': %d\n",
                line_number, count_o, count_O);

        total_o += count_o;
        total_O += count_O;
    }

    fprintf(output_file, "\nОбщее количество:\n");
    fprintf(output_file, "Маленьких 'o': %d\n", total_o);
    fprintf(output_file, "Больших 'O': %d\n", total_O);

    fclose(input_file);
    fclose(output_file);
}

int main() {
    const char input_path[] = "words.txt";
    const char output_path[] = "output.txt";
    struct timeval start, end;


    FILE *try_open = fopen(input_path, "r");
    if (try_open == NULL) {
        perror("Нэт файла");
        return 1;
    }
    fclose(try_open);

    gettimeofday(&start, NULL);
    
    process_file(input_path, output_path);

    gettimeofday(&end, NULL);

    double elapsed_time = (end.tv_sec - start.tv_sec) +
                          (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("Все в файле: %s\n", output_path);
    printf("Время выполнения: %.6f секунд\n", elapsed_time);

    return 0;
}
