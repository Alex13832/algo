/* Exercise 1.2.7, modified, Alexander Karlsson*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>


int* init(unsigned long size)
{
	int* number = malloc(size*sizeof(int));
	
	int i;
	for (i = 0; i < size; i++)
		number[i] = 1;
		
	return number;
}


/* Generates prime number according to Sieve of Eratosthenes */
int* eratosthenes(const unsigned long limit)
{
	int* primes = init(limit*2);
	int* is_prime = init(limit*2);
	int prime_counter = 0;

	unsigned long limit2 = sqrt(limit) + 1;
	unsigned long j,k,x,i;

	for (i = 2; i < limit2; i++) {
		if  (is_prime[i]) {
			j = 0;
			k = 0;
			x = i*i;

			while (j <= limit) {
				j = x + k*i;
				is_prime[j] = 0;
				k++;
			}
		}
	}

	unsigned long candidate = 2;

	while (candidate <= limit) {
		if (is_prime[candidate])
			primes[prime_counter++] = candidate;

		candidate++;
	}
	
	return primes;
}

int main(void)
{
	unsigned long limit;
	scanf("%lu",&limit);

	clock_t t0, t1;
	double time;
	t0 = clock();

	int* primes = eratosthenes(limit);

	t1 = clock();
	time = (t1 - t0) / (double)CLOCKS_PER_SEC;
	printf("Used %2.6lf s\n", time);


	//int prime, i = 0;
	//while ((prime = primes[i++]) != 1) {
	//	printf("%d\n",prime);
	//}

	return 0;
}

