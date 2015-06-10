/* ---------------------------------------------------------------------------
*Class for calculcation of prime numbers.
*Algorithm: Sieve of Eratosthenes, 
---------------------------------------------------------------------------- */
#include "prime.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

Prime::Prime(unsigned long lim) : limit(lim) {
	generate_primes(limit);	
}

void Prime::eratosthenes(unsigned long lm) {
	limit = lm;
	primes.clear();
	vector<bool> prime(limit*2,true);
	unsigned long limes = sqrt(limit)+1;
	ulong j;
	ulong k;
	ulong i2;

	for(size_t i = 2; i!=limes; ++i)	{
		if (prime[i]) {
			j = 0;
			k = 0;
			i2 = pow(i,2);
			while (j <= limit) {
				j = i2 + k*i;
				prime[j] = false;
				k++;
			}
		}
	}
	
	unsigned long prime_cand = 2;

	while (prime_cand <= limit) {
		if(prime[prime_cand]) {
			primes.push_back(prime_cand);
		}
		++prime_cand;
	}

	summ = primes.size();

}

// Returns whether number is a prime number or not
bool Prime::is_prime(unsigned long number) {
	generate_primes(number);
	vector<unsigned long> prims = get_primes();
	return prims.back() == number;
}

// Returns all primes < limit	
vector<unsigned long> Prime::get_primes() {
	return primes;
}

// Returns the number of primes < limit
unsigned long Prime::get_sum(){
	return summ;
}

// Returns the nth prime number
unsigned long Prime::getNthPrime(unsigned long nth) {
	unsigned long limit = nth*2;
	Prime p(limit);
	vector<unsigned long> vec = p.get_primes();

	while (p.get_sum() < nth) {
		limit = limit*2;
		p.generate_primes(limit);
		vec = p.get_primes();
	} 
	
	return vec[nth-1]; 
}
