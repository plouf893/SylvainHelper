#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

#define NUM_PRIMES 1000000000UL

static unsigned long long *primes = NULL;
__attribute__((constructor))
     void initialize ()
{
  printf ("Initialisation du SylvainHelper (TM)\n");
  int fd = open ("primes.bin", O_RDONLY);
  if (fd < 0) {
    perror ("open");
    exit (1);
  }
  primes = mmap (NULL, NUM_PRIMES * 8UL, PROT_READ, MAP_PRIVATE, fd, 0);
  if (primes == NULL) {
    perror ("mmap");
    exit (1);
  }
  printf ("Initialisation OK.\n");
}

unsigned long long
myfunc (unsigned long long n)
{
  unsigned long long i;

  unsigned long long back = 0;
  unsigned long long fwd = NUM_PRIMES - 1;

  if ((primes[back] > n) || (primes[fwd] < n)) {
    printf ("erreur: n devrait etre compris entre %llu et %llu\n",
	    primes[back], primes[fwd]);
    return 0;
  }

  while (back + 1 < fwd) {
    unsigned long long middle = (back + fwd) / 2;

    if (primes[middle] <= n) {
      back = middle;
    }
    else {
      fwd = middle;
    }
  }

  for (;;) {
    unsigned long long dist1 = n - primes[back];
    unsigned long long dist2 = primes[fwd] - n;
    if (dist1 == dist2) {
      return dist1;
    }
    else if (dist1 < dist2) {
      if (back == 0) {
	printf ("erreur: pas trouve");
	return 0;
      }
      back--;
    }
    else {			/* dist1 > dist2 */
      if (fwd == NUM_PRIMES - 1) {
	printf ("erreur: resultat pas trouve\n");
	return 0;
      }
      fwd++;
    }
  }
}
