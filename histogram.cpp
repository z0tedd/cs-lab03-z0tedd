#include "histogram.h"
#include <cstddef>
#include <utility>
template <typename T> pair<T, T> get_minmax(const vector<T> &numbers) {
  auto it = minmax_element(numbers.begin(), numbers.end());
  if (!numbers.size())
    return make_pair(0, 0);
  return make_pair(*(it.first), *(it.second));
}
// проблема линковки
// https://stackoverflow.com/questions/4933056/how-do-i-explicitly-instantiate-a-template-function
// https://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor
namespace std {
template class std::pair<size_t, size_t>;
template class std::vector<size_t>;
template class std::pair<double, double>;
template class std::vector<double>;
} // namespace std
template pair<double, double> get_minmax(const vector<double> &numbers);
template pair<size_t, size_t> get_minmax(const vector<size_t> &numbers);
