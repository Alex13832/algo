/** -----------------------------------------------------
* Test of line segments intersection
* Alexander Karlsson, 2015-06-30
* ------------------------------------------------------- */
#include <iostream>
#include <vector>
#include "../geometry2d.cc"
#include "../../matplotlibcpp.h"
using namespace std;
namespace plt = matplotlibcpp;


int main() {
	point p1,p2,p3,p4;
	p1.x = 1; p1.y = 1;
	p2.x = 6; p2.y = 6;
	p3.x = 2; p3.y = 6;
	p4.x = 5; p4.y = 2;

	vector<int> px1{1,6}, px2{2,5}, py1{1,6}, py2{6,2};

	cout << segment_intersect(p1,p2,p3,p4) << endl;

	plt::plot(px1,py1,"-r");
	plt::plot(px2,py2,"-r");
	plt::plot(px1,py1,"or");
	plt::plot(px2,py2,"or");
	

	p1.x = 5; p1.y = 6;
	p2.x = 10; p2.y = 10;
	p3.x = 8; p3.y = 6;
	p4.x = 10; p4.y = 5;

	vector<int> px3{5,10}, px4{8,10}, py3{6,10}, py4{6,5};

	cout << segment_intersect(p1,p2,p3,p4) << endl;

	plt::plot(px3,py3,"-k");
	plt::plot(px3,py3,"ok");
	plt::plot(px4,py4,"-k");
	plt::plot(px4,py4,"ok");

	plt::xlim(0, 10);
	plt::ylim(0, 10);
	plt::show();
}