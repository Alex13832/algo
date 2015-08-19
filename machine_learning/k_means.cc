/** --------------------------------------------------------------
* K-means clustering algorithm. Convergence speed depends on
* the chosen value on k, the number of data elements and the 
* magnitude of the data elements.
* With k == 5 and 1 000 000 elenents --> No problems.
* Alexander Karlsson, 2015-08-16
* ---------------------------------------------------------------- */
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <iostream>
using namespace std;

#define DBL_MAX 1.79769e+308


struct Item {
	int x,y;	
};

/* Compute the (euclidian) distance */
double distance(int x1, int x2, int y1, int y2) {
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

/* K-means clustering algorithm. Returns the clusters as vector<Item>[k]
 where i...k is the i:th cluster. */
vector<vector<Item>> k_means(vector<Item> data, const int k) {
	if (k <= 1) throw -1;

	size_t N = data.size();
	vector<Item> centroids(k);
	vector<vector<Item>> clusters(k);
	vector<int> x_mean(k), y_mean(k);

	/* initialize random seed: */
 	srand (time(NULL));
  	for (int i = 0; i < k; ++i) {
  		size_t location = rand() % N;
  		centroids[i] = data[location];
  	}

  	
  	int conv = 0;
  	int old;
  	/* Repeat unitl convergence */
  	while (conv < 10) {
  		for (int i = 0; i < k; ++i) clusters[i].clear();

	  	for (auto item: data) {
	  		int x1 = item.x, y1 = item.y;
	  		double min_dist = DBL_MAX;
	  		int index = -1;

	  		/* Find the closest centroid */
	  		for (int i = 0; i < k; ++i) {
	  			Item centroid = centroids[i];
	  			int x2 = centroid.x, y2 = centroid.y;
	  			double dist = distance(x1,x2,y1,y2);

	  			if (dist < min_dist) {
	  				min_dist = dist;
	  				index = i;
	  			}
	  		}
	  		
	  		clusters[index].push_back(item);
	  		x_mean[index] += item.x;
	  		y_mean[index] += item.y;
	  	}

	  	/* Find the mean center of new centroids */
	  	for (int i = 0; i < k; ++i) {
	  		if (clusters[i].size() != 0) {
		  		x_mean[i] /= clusters[i].size();
		  		y_mean[i] /= clusters[i].size();

		  		centroids[i].x = x_mean[i];
		  		centroids[i].y = y_mean[i];
		  		x_mean[i] = 0;
		  		y_mean[i] = 0;
	  		}
	  	}
	  	cout << conv << endl;
	  	/* Decide if the cluster converges */
	  	if (centroids[0].x == old) conv++;
	  	else conv = 0;

	  	old = centroids[0].x;
 	}

 	return clusters;

}