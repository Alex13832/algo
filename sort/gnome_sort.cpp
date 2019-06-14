/** ----------------------------------------------------------
* Gnome sort algorithm.
* 2016-06-28
* ------------------------------------------------------------ */

#include <iostream>
#include <vector>
#include <algorithm>

template <typename T> void gnome_sort(vector<T>& vec)
{
    int i = 0;
    int n = vec.size();

    while (i < n) {

        if (i == 0)
            i++;
        if (vec[i] >= vec[i-1])
            i++;
        else {
            swap(vec[i], vec[i-1]);
            i--;
        }
    }
}