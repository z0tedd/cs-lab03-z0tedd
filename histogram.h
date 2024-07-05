#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

template <typename T> pair<T, T> get_minmax(const vector<T> &numbers);
//
// {
//   auto it = minmax_element(numbers.begin(), numbers.end());
//   return make_pair(*(it.first), *(it.second));
// }
#endif
