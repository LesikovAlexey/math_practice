#include "galois.h"
GField::GField() : degree(0), irred_poly(0) {}

GField::GField(int deg, GFElement poly) : degree(deg), irred_poly(poly)
{
    GFElement buf1;
    GFElement buf2;
    mult_table = (GFElement *)malloc((int)pow(2, degree) * (int)pow(2, degree) * sizeof(GFElement));
    for (int i = 0; i < (int)pow(2, degree); i++) {
        for (int j = 0; j < (int)pow(2, degree); j++) {
            mult_table[i + (int)pow(2, degree) * j] = (int *)malloc(degree * sizeof(int));
        }
    }
    buf1 = (int *)malloc(degree * sizeof(int));
    buf2 = (int *)malloc(degree * sizeof(int));
    for (int i = 0; i < (int)pow(2, degree); i++) {
        for (int j = 0; j < (int)pow(2, degree); j++) {
            to_poly(i, buf1);
            to_poly(j, buf2);
            this->mult(buf1, buf2, mult_table[i + (int)pow(2, degree) * j]);
        }
    }
    irred_poly_degree = 0;
    while (irred_poly[irred_poly_degree] != 1) {
        irred_poly_degree ++;
    }
    free(buf1);
    free(buf2);
}

GField::~GField() 
{
    free(mult_table);
}

int GField::to_poly (const int a, GFElement poly)
{
    int buf = a;
    for (int i = degree - 1; i > -1; i--) {
        poly[i] = (buf % 2);
        buf = buf / 2;
    } 
}
int GField::to_int (GFElement a)
{
    int buf = 0;
    for (int i = degree - 1; i > -1; i--) {
        if(a[i] == 1) {
            buf += pow(2, degree - 1 - i);
        }     
    }
    return buf;
}

int GField::plus(const GFElement a, const GFElement b, GFElement result)
{
    for (int i = 0; i < degree; i++) {
        result[i] = a[i] ^ b[i];
    }
    return 0;
}

int GField::minus(const GFElement a, const GFElement b, GFElement result)
{
    for (int i = 0; i < degree; i++) {
        result[i] = a[i] ^ b[i];
    }
    return 0;
}

int GField::mult(const GFElement a, const GFElement b, GFElement result)
{
    int* buf;
    buf = (int*)calloc(2 * degree - 1 , sizeof(int));
    for (int i = 0; i < degree; i++) {                      //перемножение многочленов
        if (b[i] == 1) {
            for (int j = 0; j < degree; j++) {
                buf[i + j] ^= a[j];
            }
        }
    }
    for (int i = 0; i < degree; i++) {                       //остаток от деления на заданный неприводимый многочлен
        if (buf[i] == 1) {
            for (int j = 0; j < degree + 1; j ++) {
                if (irred_poly[j] == 1) {
                    buf[i + j] ^= 1;
                }
            }
        }
    }
    for (int i = 0; i < degree; i++) {                      
        result[i] = buf[degree - 1 + i];
    }
    free(buf);
    return 0;
}

int GField::div(const GFElement a, const GFElement b, GFElement result)
{
    int a_int = to_int(a);
    int b_int = to_int(b);
    for (int i = 0; i < (int)pow(2, degree); i ++) {
        if (to_int(mult_table[a_int * (int)pow(2, degree) + i]) == b_int) {
            result = mult_table[i];
            break;
        }
    }
    
}
int GField::power(const GFElement a, int n, GFElement result)
{
    int* buf;
    int* buf1;
    buf = (int*)calloc(degree, sizeof(int));
    buf1 = (int*)calloc(degree, sizeof(int));
    buf[degree - 1] = 1;
	while (n) {
		if (n & 1)
            mult(buf, a, buf);
        mult(a, a, buf1);
		n >>= 1;
	}
    result = buf;
    free(buf);
    free(buf1);
    return 0; 
}

int main (int argc, char** argv) 
{
    char symb;
    GFElement a, b, irred_poly, c;
    int degree;
    FILE* input_file;
    if (argc != 2) {
        printf("./galois <input_file>\n");
        return -1;
    }
    input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        printf("unable to open file\n");
        fclose(input_file);
        return -2;
    }
    if (fscanf(input_file, "%d", &degree) != 1 || degree < 1) {
        printf("incorrect degree\n");
        fclose(input_file);
        return -1;
    }
    irred_poly = (int*)calloc((degree + 1), sizeof(int));
    a = (int*)calloc(degree, sizeof(int));
    b = (int*)calloc(degree, sizeof(int));
    c = (int*)calloc(degree, sizeof(int));
    fgetc(input_file);
    for (int i = 0; i < degree + 1; i++) {
        irred_poly[i] = fgetc(input_file) - '0';
    }
    fgetc(input_file);
    for (int i = 0; i < degree; i++) {
        a[i] = fgetc(input_file) - '0';
    }
    fgetc(input_file);
    for (int i = 0; i < degree + 1; i++) {
        b[i] = fgetc(input_file) - '0';
    }
    fclose(input_file);
    GField F;
    F = GField(degree, irred_poly);
    
    for (int i = 0; i < degree; i++) {
        printf("%d ", a[i]);
    }
    printf(" -  a = %d\n", F.to_int(a));
    for (int i = 0; i < degree; i++) {
        printf("%d ", b[i]);
    }
    printf(" -  b = %d\n", F.to_int(b));
    
    F.plus(a, b, c);
    printf("a + b = ");
    for (int i = 0; i < degree; i++) {
        printf("%d ", c[i]);
    }
    printf("= %d\n", F.to_int(c));

    F.minus(a, b, c);
    printf("a - b = ");
    for (int i = 0; i < degree; i++) {
        printf("%d ", c[i]);
    }
    printf("= %d\n", F.to_int(c));

    F.mult(a, b, c);
    printf("a * b = ");
    for (int i = 0; i < degree; i++) {
        printf("%d ", c[i]);
    }
    printf("= %d\n", F.to_int(c));

    F.div(a, b, c);
    printf("a / b = ");
    for (int i = 0; i < degree; i++) {
        printf("%d ", c[i]);
    }
    printf("= %d\n", F.to_int(c));

    F.power(a, F.to_int(b), c);
    printf("a ^ b = ");
    for (int i = 0; i < degree; i++) {
        printf("%d ", c[i]);
    }
    printf("= %d\n", F.to_int(c));
    free(a);
    free(b);
    free(c);
    free(irred_poly);
    return 0;
}