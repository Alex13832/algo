/* ----------------------------------------------------------------------------
* Tests for Bagging  
* Alexander Karlsson, 2015-08-19
* -----------------------------------------------------------------------------*/
#include "../bagging.cc"
#include "../../matplotlibcpp.h"
namespace plt = matplotlibcpp;

int main(int args, char *argv[]) {

	string file = "bagging/sample_data8";
	string file_real = "bagging/real_data8";

	ValMat data = train(file);
	plt::plot(data[0],"o");
	ValMat real = train(file_real);
	int iterations = stoi(argv[1]);
	vector<double> bagg = bagging(data,iterations);

	plt::plot(real[0]);
	plt::plot(bagg);
	plt::show();

}