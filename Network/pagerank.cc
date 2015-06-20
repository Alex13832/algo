/**-----------------------------------------------------------
* Implementation of the PageRank algorithm.
* The vectors pushed-back in the root vector should contain
* (in most cases) the column of the transition matrix.
* Alexander Karlsson, 2015-06-20
* ------------------------------------------------------------ */
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <climits>
#include <chrono>
#include <limits>
using namespace std;

#define DBL_MAX 1.7976931348623158e+308 

/* Returns a vector with uniformly distributed random numbers [0 1]*/
vector<double> rand_vec(int N) {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  	default_random_engine generator (seed);
	uniform_real_distribution<double> distribution (0.0,1.0);
	
	vector<double> rand(N);
	for (size_t i = 0; i < rand.size(); i++) {
		rand[i] = distribution(generator);
	}
	return rand;
}

/* Euclidean norm */
double norm(vector<double> vec) {
	double temp = 0;

	for (size_t i = 0; i < vec.size(); i++) {
		temp += pow(vec[i],2);
	}

	return sqrt(temp);
}


/* L1 norm */
double norm1(vector<double> vec) {
	double temp = 0;

	for (size_t i = 0; i < vec.size(); i++) {
		temp += abs(vec[i]);
	}

	return temp;
}

/* "Matlab" dot division*/
void matrix_dot_div(vector<double>& vec, double d) {
	for_each(vec.begin(),vec.end(),[&](double& i){
		i = i/d;
	});
}

/* Matrix scalar multiplication */
void scalar_mult(vector<vector<double>>& mat, double d) {
	for(auto& vec: mat) {
		for(auto& entry: vec) {
			entry *= d;
		}
	}
}

/* Addition of two matrices */
vector<vector<double>> matrix_add(vector<vector<double>> lhs, vector<vector<double>> rhs) {
	vector<vector<double>> temp = lhs;

	for (size_t i = 0; i < lhs.size(); i++) {
		for(size_t j = 0; j < lhs[i].size(); j++) {
			temp[i][j] = lhs[i][j] + rhs[i][j];
		}
	}

	return temp;
}
 /* Multiplication of a Matrix and a vector */
vector<double> mat_vec_mult(vector<vector<double>> A, vector<double> v) { 
	vector<double> vtemp(v.size(),0);

	for(size_t i = 0; i < A.size(); i++){
		for (size_t j = 0; j < A[i].size(); j++) {
			vtemp[i] += A[j][i]*v[j];
		}
	}

	return vtemp;
}

vector<vector<double>> transition_mat(vector<vector<int>> M, vector<int> degree) {
	size_t N = M.size();
	vector<vector<double>> p(N,vector<double>(N));

	for(size_t i = 0; i < N; i++) {
		for (size_t j = 0; j < N; j++) {
			double d = 0.9*((double )M[i][j]/ (double) degree[i])+0.1/N;
			p[i][j] = d;
		}
	}

	return p;
}

/**
* M: web graph
* d: damping factor
* err: convergence treshold
*/
vector<double> page_rank(vector<vector<double>> M, double d, double error) {
	int sz = M.size();
	vector<double> vr = rand_vec(sz);
	double nrm = norm1(vr);
	matrix_dot_div(vr, nrm);
	vector<double> v_end(sz, DBL_MAX);
	double q = (1-d)/sz;
	scalar_mult(M,d);
	vector<vector<double>> rhs(sz, vector<double>(sz,q));
	 
	vector<vector<double>> M_hat = matrix_add(M,rhs);
	double norm_calc = DBL_MAX;

	while (norm_calc > error) {
		v_end = vr;
		vr = mat_vec_mult(M_hat, vr);

		vector<double> temp(vr.size(),0);
		for (size_t i = 0; i < vr.size(); i++) {
			temp[i] = vr[i] - v_end[i];
		}

		norm_calc = norm(temp);
	}

	return vr; 
}