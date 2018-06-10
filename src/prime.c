#include <math.h>

long* sieve_of_erathosenes(long n) {
        // Initialize all numbers from 2 to n to 1 (a prime number)
        short* is_prime[n - 2] = {1};

        for (int i = 2; i < sqrt((double)n); i++) {
                if (is_prime[i]) {
                        for (int j = (int)pow((double) i, 2); j < n; j += (n * i)) {
                                is_prime[i] = 0;
                        }
                }
        }

        int offset = 3;
        int size = (int)sqrt((double)n);
        long* nums[size] = {};
        for (int x = 0; x < size; x++) {
                if (is_prime[x]) {
                        nums[x] = (long)(x + offset);
                }
        }

        return nums;
}
