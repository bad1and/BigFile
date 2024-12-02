#include <stdio.h>
#include <time.h>

int main() {
    char textBuffer[2048];
    FILE *input = fopen("lab4.txt", "r");
    FILE *output = fopen("output.txt", "w");


    clock_t startTime = clock();

    if (input) {
        int capitalOCount = 0, smallOCount = 0;
        int totalCapitalO = 0, totalSmallO = 0;
        int lines = 1;
        int b_index = 0;

        while ((textBuffer[b_index] = fgetc(input)) != EOF) {
            if (textBuffer[b_index] == '\n') {
                fprintf(output, "Строка: %3d   Букв О: %3d   Букв о: %3d\n", lines, capitalOCount, smallOCount);
                totalCapitalO += capitalOCount;
                totalSmallO += smallOCount;
                capitalOCount = 0;
                smallOCount = 0;
                lines++;
            } else if (textBuffer[b_index] == 'O') {
                capitalOCount++;
            } else if (textBuffer[b_index] == 'o') {
                smallOCount++;
            }

            b_index = (b_index + 1) % 2048; // очистака при переполнении
        }


        if (capitalOCount > 0 || smallOCount > 0) {
            fprintf(output, "Строка: %3d   Букв О: %3d   Букв о: %3d\n", lines, capitalOCount, smallOCount);
            totalCapitalO += capitalOCount;
            totalSmallO += smallOCount;
        }


        fprintf(output, "\nОбщее количество:\n");
        fprintf(output, "Всего строк: %d\n", lines);
        fprintf(output, "Всего букв О: %d\n", totalCapitalO);
        fprintf(output, "Всего букв о: %d\n", totalSmallO);

        fclose(input);
        fclose(output);
    } else {
        printf("No file.\n");
        return 1;
    }

    // Замер времени завершения программы
    clock_t endTime = clock();
    double executionTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    // Вывод времени выполнения в консоль
    printf("Программа завершена за %.3f секунд.\n", executionTime);

    return 0;
}
