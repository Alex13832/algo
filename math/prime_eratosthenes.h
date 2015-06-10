#ifndef PRIME_H
#define PRIME_H

#include <iostream>
#include <vector>

class Prime {
	public:
		Prime(unsigned long limit);
		std::vector<unsigned long> get_primes();
		void eratosthenes(unsigned long limes);
		unsigned long get_sum();
		unsigned long getNthPrime(unsigned long nth);
		bool is_prime(unsigned long number);
	private:
		unsigned long limit;		
		std::vector<unsigned long> primes;
		unsigned long summ;
};

#endif
