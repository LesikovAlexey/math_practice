#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
typedef int* GFElement;
class GField 
{
public:
    int plus(const GFElement a, const GFElement b, GFElement result);
    int minus(const GFElement a, const GFElement b, GFElement result);
    int mult(const GFElement a, const GFElement b, GFElement result);
    int div(const GFElement a, const GFElement b, GFElement result);
    int power(const GFElement a, int n, GFElement result);
    GField();
    GField(int deg, GFElement poly); 
    ~GField();
    int to_poly (const int a, GFElement poly);
    int to_int (GFElement a);
private:
    int degree; // размерность поля 2^degree
    GFElement irred_poly;
    int irred_poly_degree;
    GFElement* mult_table;

};
unsigned long long currentTimeNano()
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (long long)(t.tv_sec * 1e9 + t.tv_nsec);
}