#include <stdio.h>
#include <unistd.h>

int main(void) {
    char buf[1024];
    int nread = 0;
    while (fgets(buf, 1024, stdin) != NULL) {
        nread++;
        if (!(nread % 1000000 )) {
            printf("%u %% converted\n", nread / 1000000);
        }
        unsigned long long primes[10];
        sscanf(buf, "%llu %llu %llu %llu %llu %llu %llu %llu %llu %llu", primes, primes + 1, primes + 2, primes + 3, primes + 4, primes + 5, primes + 6, primes + 7, primes + 8, primes + 9);
        write(2, &primes, sizeof(primes));
    }
}
