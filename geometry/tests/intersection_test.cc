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
	string linecol1 = "-r", linecol2 = "-k";
	string dotcol1 = "or", dotcol2 = "ok";
	string linecol,dotcol;

	point p1,p2,p3,p4;
	p1.x = 1; p1.y = 1;
	p2.x = 5; p2.y = 5;
	p3.x = 1; p3.y = 4;
	p4.x = 5; p4.y = 1;

	vector<int> px1{1,5}, px2{1,5}, py1{1,5}, py2{4,1};

	if (segment_intersect(p1,p2,p3,p4)) {
		linecol = linecol1;
		dotcol = dotcol1;
	} else { 
		linecol = linecol2;
		dotcol = dotcol2;
	}

	plt::plot(px1,py1,linecol);
	plt::plot(px2,py2,linecol);
	plt::plot(px1,py1,dotcol);
	plt::plot(px2,py2,dotcol);
	

	p1.x = 7; p1.y = 1;
	p2.x = 11; p2.y = 5;
	p3.x = 10; p3.y = 3;
	p4.x = 12; p4.y = 1;

	vector<int> px3{7,11}, px4{10,12}, py3{1,5}, py4{3,1};

	if (segment_intersect(p1,p2,p3,p4)) {
		linecol = linecol1;
		dotcol = dotcol1;
	} else { 
		linecol = linecol2;
		dotcol = dotcol2;
	}

	plt::plot(px3,py3,linecol);
	plt::plot(px3,py3,dotcol);
	plt::plot(px4,py4,linecol);
	plt::plot(px4,py4,dotcol);


	p1.x = 15; p1.y = 1;
	p2.x = 19; p2.y = 5;
	p3.x =19; p3.y = 5;
	p4.x = 22; p4.y = 2;
	
	vector<int> px5{15,19}, px6{19,22}, py5{1,5}, py6{5,2};
	
	if (segment_intersect(p1,p2,p3,p4)) {
		linecol = linecol1;
		dotcol = dotcol1;
	} else { 
		linecol = linecol2;
		dotcol = dotcol2;
	}

	plt::plot(px5,py5,linecol);
	plt::plot(px5,py5,dotcol);
	plt::plot(px6,py6,linecol);
	plt::plot(px6,py6,dotcol);
















	plt::xlim(0, 23);
	plt::ylim(0, 6);





	plt::show();






}
