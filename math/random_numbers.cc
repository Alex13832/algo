/** --------------------------------------------------------------------------
* Functions for generation (pseudo) random numbers according to some 
* distribution: Uniform, Exponential, Normal, Weibull, Binomial, Gamma, 
* Poisson, Erlang, Geometric.
* Alexander Karlsson, begun 2015-08-25
* ---------------------------------------------------------------------------- */
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <ctime>
using namespace std;

#define PI  3.14159265358979323846
#define E   2.71828182845904523536
// YES PSEUDO RANDOM

/* Returns a uniform random number */
double randu(double a, double b) {    
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        mt19937 generator(seed); //Mersenne twister
        uniform_real_distribution<double> distribution(a,b);
        return distribution(generator);
}


/* Exponential distributed random number */
double rand_exp(double lambda) {
        if (lambda == 0.0) throw -1;
        double r = randu(0.0, 1.0);
        return -log(r)/lambda;
}


/* Normal distributed random numbers */
pair<double,double> rand_norm(double mu, double sigma) {
        double r1 = randu(0.0, 1.0); 
        double r2 = randu(0.0, 1.0);
        double n1 = mu + sigma*cos(2*PI*r1)*sqrt(-2*log(r2));
        double n2 = mu + sigma*sin(2*PI*r1)*sqrt(-2*log(r2));
        return pair<double,double>(n1,n2);
}


/* Weibull distributed random number */
double rand_weib(double lambda, double c) {
        double r = randu(0.0,1.0);
        return pow(-log(r),1.0/c)/lambda;
}


/* Binomial distributed random number */
double rand_bin(int n, double p) {
        vector<double> U(n);
        vector<int> V(n);
        for (auto& u: U) u = randu(0.0,1.0);

        transform(U.begin(), U.end(), V.begin(), [&](double& d) {
                if (d < p) return 0;
                else return 1;
        });
  
        return accumulate(V.begin(), V.end(), 0);
}


/* Gamma distributed random number */
double rand_gamma(int n, double lambda) {
        vector<double> U(n);
        for (auto& u: U) u = randu(0.0,1.0);

        transform(U.begin(),U.end(),U.begin(),[&](double d) {
                return -log(d)/lambda;
        });

        return accumulate(U.begin(),U.end(), 0.0);     
}


/* Poisson distributed random number */
int rand_poisson(int lambda) {
        double L = pow(E,-lambda), p = 1.0;
        int k = 0;

        do {
                k++;
                double u = randu(0.0,1.0);
                p *= u;
        } while (p > L);

        return k - 1;
}


/* Erlang distributed random number */
double rand_erlang(int k, double mu) {
        double u = 1.0;
        for (int i = 0; i < k; ++i) {
                u *= randu(0.0,1.0);
        }

        return -log(u)/mu;
}


/* Geometric distributed random number */
int rand_geom1(double p) {
        int k = 0;
        double x = randu(0.0,1.0);

        while (x > p) {
                x = randu(0.0,1.0);
                k++;
        }

        return k;
}