#include <stdlib.h>
#include <stdio.h>

char sieve[100000], subsieve[100000];
int primes[25000];
int num_primes;

void init_primes()
{
  primes[0] = 2;

  while (primes[num_primes] < 31623) /* sqrt(1 billion) */
  {
    int i, p = primes[num_primes];

    for (i = 2 * p; i < 31623; i += p)
      sieve[i] = 1;

    for (i = p + 1; sieve[i]; i++)
      ;

    primes[++num_primes] = i;
  }

  num_primes++;
}

void run_sieve(int low, int high)
{
  int i, j, p;

  memset(sieve, 0, high - low + 1);

  for (i=0; i < num_primes; i++)
  {
    p = primes[i];

    if (p > high)
      break;

    if (low <= p)
      j = p * 2;
    else
      j = low + p - ((low - 1) % p) - 1;

    while (j <= high)
    {
      sieve[j - low] = 1;
      j += p;
    }
  }
}

void process()
{
  /* assume input is valid */
  int i, num_test_cases;

  scanf("%d", &num_test_cases);

  for (i=0; i < num_test_cases; i++)
  {
    int j, low, high;

    scanf("%d", &low);
    scanf("%d", &high);

    if (low < 2)
      low = 2;

    run_sieve(low, high);

    for (j=low; j <= high; j++)
      if (!sieve[j - low])
        printf("%d\n", j);

    if (i + 1 < num_test_cases)
      printf("\n");
  }
}

int main()
{
  init_primes();

  process();

  return 0;
}
