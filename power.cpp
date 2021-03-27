#include "power.h"

int main(int argc, char** argv)
{
    int a;
    int n;
    FILE* output_file;
    unsigned long long time;
    time = currentTimeNano();
    if (argc != 4) {
        printf("./power a n <output file>\n");
        return -1;
    }
    if (sscanf(argv[1], "%d", &a) != 1) {
        printf("./power a n <output file>\n");
        return -1;
    }
    if (sscanf(argv[2], "%d", &n) != 1) {
        printf("./power a n <output file>\n");
        return -1;
    }
    time = currentTimeNano() - time;
    output_file = fopen(argv[3], "w");
    if (output_file == NULL) {
        printf("unable to open file %s", argv[3]);
        fclose(output_file);
        return -2;
    } 
    fprintf(output_file, "%d", pow(a, n));
    printf("%10.3e nanosec\n", (double)time);
    fclose(output_file);
    return 0;
}

