/** ---------------------------------------------------------------------------
 Bucket sort algorithm.
 Alexander Karlsson 2016-10-02
----------------------------------------------------------------------------- */
#include <vector>
#include <algorithm>

using namespace std;

void bucket_sort(vector<int>& array)
{
    auto maxElemPtr = max_element(array.begin(), array.end());
    int nbrOfBuckets = sqrt(*maxElemPtr);
    vector<vector<int>> buckets(nbrOfBuckets+1);

    /* Put in buckets */
    for (int& x: array) {
        buckets[(int)sqrt(x)].push_back(x);
        x = 0;
    }

    /* Put back elements */
    int count = 0;
    for (vector<int> bucket: buckets) {
        for (int e: bucket)
            array[count++] = e;
    }

    /* Insertion sort (Bentley 1993) */
    for (size_t i = 1; i < array.size(); i++) {
        for (size_t j = i; j > 0 && array[j-1] > array[j]; j--)
            swap(array[j], array[j-1]);
    }
}
