/** --------------------------------------------------------------------------
* Tests for generating random numbers.
* Alexander Karlsson, begun 2015-08-25
* ---------------------------------------------------------------------------- */
#include "../random_numbers.cc"
#include <vector>
#include <algorithm>
#include "../../matplotlibcpp.h"
#include <python2.7/Python.h>
namespace plt = matplotlibcpp;


/** 
choice == 0 -> Exponential distribution
choice == 1 -> Normal distribution
choice == 2 -> Weibull distribution
choice == 3 -> Gamma distribution
choice == 4 -> Erlang distribution
*/
void test_cont_rand(int choice) {
	vector<double> x1,x2,x3,x4,y;
	double d = 1.0/10000.0, insr = 0.0;

	for (int i = 0; i < 10000; ++i) {

		switch(choice) {
			case 0:
				x1.push_back(rand_exp(0.5));
				x2.push_back(rand_exp(1.0));
				x3.push_back(rand_exp(1.5));
				x4.push_back(rand_exp(2.0));
			break;

			case 1:
				x1.push_back(rand_norm(0.0,0.2).first);
				x2.push_back(rand_norm(0.0,1.0).first);
				x3.push_back(rand_norm(0.0,5.0).first);
				x4.push_back(rand_norm(-2.0,0.5).first);			
			break;

			case 2:
				x1.push_back(rand_weib(1.0,0.5));
				x2.push_back(rand_weib(1.0,1.0));
				x3.push_back(rand_weib(1.0,1.5));
				x4.push_back(rand_weib(1.0,5.0));
			break;

			case 3:
				x1.push_back(rand_gamma(1,2.0));
				x2.push_back(rand_gamma(2,2.0));
				x3.push_back(rand_gamma(3,2.0));
				x4.push_back(rand_gamma(5,1.0));
			break;

			case 4:
				x1.push_back(rand_erlang(1,2.0));
				x2.push_back(rand_erlang(3,2.0));
				x3.push_back(rand_erlang(7,0.5));
				x4.push_back(rand_erlang(9,1.0));
			break;

		}

		y.push_back(insr);
		insr += d;
	}

	sort(x1.begin(), x1.end());
	sort(x2.begin(), x2.end());
	sort(x3.begin(), x3.end());
	sort(x4.begin(), x4.end());

	plt::plot(x1,y,"r.");
	plt::plot(x2,y,"y.");
	plt::plot(x3,y,"k.");
	plt::plot(x4,y,"b.");
	
	plt::show();

}

/** 
choice == 0 -> poisson distribution
choice == 1 -> geometric distribution
choice == 2 -> binomail distribution
*/
void test_disc_rand(int choice) {
	vector<double> x1,x2,x3,y;
	double d = 1.0/10000.0, insr = 0.0;

	for (int i = 0; i < 10000; ++i) {

		switch (choice) {
			case 0: 
				x1.push_back(rand_poisson(1));
				x2.push_back(rand_poisson(4));
				x3.push_back(rand_poisson(10));
			break;

			case 1:
				x1.push_back(rand_geom1(0.2));
				x2.push_back(rand_geom1(0.5));
				x3.push_back(rand_geom1(0.8));
			break;	

			case 2:
				x1.push_back(rand_bin(20,0.5));
				x2.push_back(rand_bin(20,0.7));
				x3.push_back(rand_bin(40,0.5));
			break;
		}

		y.push_back(insr);
		insr += d;
	}

	sort(x1.begin(), x1.end());
	sort(x2.begin(), x2.end());
	sort(x3.begin(), x3.end());


	vector<double> y1(y.size()), y2(y.size()), y3(y.size());
	double ya = y[0], yb = ya, yc = ya;
	for (size_t i = 1; i < x1.size(); ++i) {

		if (x1[i-1] == x1[i]) y1[i-1] = ya;
		else ya = y[i-1];
		if (x2[i-1] == x2[i]) y2[i-1] = yb;
		else yb = y[i-1];
		if (x3[i-1] == x3[i]) y3[i-1] = yc;
		else yc = y[i-1];
	}	

	plt::plot(x1,y1,"y.");
	plt::plot(x2,y2,"m.");
	plt::plot(x3,y3,"c.");
	
	plt::show();

}

int main() {
	cout << "Testing Exponential distributed random numbers" << endl;
	test_cont_rand(0); //Exp
	cout << "Testing Normal distributed random numbers" << endl;
	test_cont_rand(1); //Norm
	cout << "Testing Weibull distributed random numbers" << endl;
	test_cont_rand(2); //Weib
	cout << "Testing Gamma distributed random numbers" << endl;
	test_cont_rand(3); //Gamma
	cout << "Testing Erlang distributed random numbers" << endl;
	test_cont_rand(4); //Erlang

	cout << "Testing Poisson distributed random numbers" << endl;
	test_disc_rand(0); //Poisson
	cout << "Testing Geometrical distributed random numbers" << endl;
	test_disc_rand(1); //Geom.
	cout << "Testing Binomial distributed random numbers" << endl;
	test_disc_rand(2); //Bin
	
}	