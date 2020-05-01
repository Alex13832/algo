/* ----------------------------------------------------------------------------
* Bootstrap Aggregation, Bagging
* Sample data, each line is one sample
* First line is how many sets of samples, second line is how many samples  
*
* http://www.burns-stat.com/documents/tutorials/the-statistical-bootstrap-
* and-other-resampling-methods-2/ was very helpful.
*
* Alexander Karlsson, 2015-08-19
* -----------------------------------------------------------------------------*/
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdlib.h>
using namespace std;

typedef vector<vector<double>> ValMat;

/* Train data */
ValMat train(string filename) {
        ifstream file(filename);
        string line;
        getline(file,line);
        size_t sets = stoi(line);
        getline(file,line);
        size_t samples = stoi(line);

        ValMat data(sets,vector<double>(samples));

        int sample_count = 0;

        /* Get line and split by whitespace */
        while (getline(file, line)){
                vector<string> line_content; 
                string str(line);
                string buf; 		// buffer string
                stringstream ss(str);   // stream

                while (ss >> buf) line_content.push_back(buf);

                for (size_t i = 0; i < samples; ++i) {
                	double sample = stod(line_content[i]);
                	data[sample_count][i] = sample;
                }
                sample_count++;
        }

        return data;
}

/* Bootstrap Aggregation */
vector<double> bagging(ValMat data, int iterations) {
	/* Determine size */
	size_t sets = data.size(), samples = data[0].size();
	/* initialize random seed: */
 	srand (unsigned (time(0) ) );
 	vector<double> sample(samples,0);

 	/* Pick "fake" samples many times, make it unbiased */
 	for (int i = 0; i < iterations; ++i) {
 		for(size_t j = 0; j < samples; ++j) {
 			size_t rand_pos = rand() % sets;
 			sample[j] += data[rand_pos][j];
 		}
 	}

 	/* Take the mean of all picked samples */
 	for (size_t i = 0; i < samples; ++i) sample[i] /= (iterations);

 	return sample;	
}