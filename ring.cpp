#include "ring.h"
#include <stdio.h>
int main(int argc, char** argv)
{
    int n;
    int a;
    int b;
    int buf = 0;
    char c;
    FILE* input_file;
    if (argc != 3) {
        printf("./ring n <input_file>\n");
        return -1;
    }
    if (sscanf(argv[1], "%d", &n) != 1) {
        printf("incorrect arguments\n");
        return -1;
    }
    input_file = fopen(argv[2], "r");
    if (input_file == NULL) {
        printf("unable to open file\n");
        fclose(input_file);
        return -2;
    }
    while ((c = fgetc(input_file)) != EOF) {
        if (c == '0' || c == '1') {
            buf *= 2;         
            buf += (c - '0');        
        }
        if (c == ' ') {
            a = buf;
            buf = 0;
        }
    }
    b = buf;
    fclose(input_file);
    if (a >= n || b >= n) {
        printf("incorrect arguments\n");
        return -1;
    }
    printf("%d + %d mod %d = %d\n", a, b, n, (Residue(a, n) + Residue(b, n)).a);
    printf("%d - %d mod %d = %d\n", a, b, n, (Residue(a, n) - Residue(b, n)).a);
    printf("%d * %d mod %d = %d\n", a, b, n, (Residue(a, n) * Residue(b, n)).a);
    printf("pow(%d, %d) mod %d = %d\n", a, b, n, Residue(a, n).power(Residue(b, n)).a);

    return 0;
}