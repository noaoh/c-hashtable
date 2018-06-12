#include <math.h>
#include "prime.h"

int is_prime(const int x) {
        if (x < 2) { return -1; }
        if (x < 4) { return 1; }
        if ((x % 2) == 0 || (x % 3) == 0) { return 0; }
        int i = 5;
        int w = 2;

        while(pow(i, 2) <= x) {
                if (x % i == 0) {
                        return 0;
                }
                
                i += w;
                w = 6 - w;
        }

        return 1;
}

int next_prime(int x) {
        while(is_prime(x) != 1) {
                x++;
        }
        return x;
}
