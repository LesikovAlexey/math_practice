#include "power.h"
class Residue 
{
private:
    int n;
    
public:
    int a;
    Residue(int i, int k) : a(i), n(k)
    {}
    
    const Residue operator+(const Residue& r) const {
        return Residue(a + r.a - r.n * (a + r.a >= r.n), n);
    }

    const Residue operator-(const Residue& r) const {
        return Residue(a - r.a + r.n * (a < r.a), n);
    }

    const Residue operator*(const Residue& r) const {
        return Residue(a * r.a % n, n);
    }
    const Residue power(const Residue r) {
        return Residue(pow(a, r.a) % n, n);
    }
};