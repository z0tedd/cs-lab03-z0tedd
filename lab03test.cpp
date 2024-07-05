#include "histogram.h"

#include <cassert>
void test_positive() {
  vector<double> m = {1, 2, 3};
  auto [min, max] = get_minmax(m);
  assert(min == 1);
  assert(max == 3);
}
void test_equal() {
  vector<double> m = {1, 1, 1};
  auto [min, max] = get_minmax(m);
  assert(max == 1);
  assert(min == 1);
}
void test_negative() {
  vector<double> m = {-1, -2, -3};
  auto [min, max] = get_minmax(m);
  assert(max == -1);
  assert(min == -3);
}
void test_one() {
  vector<double> m = {-1};
  auto [min, max] = get_minmax(m);
  assert(max == -1);
  assert(min == -1);
}
void test_empty() {
  vector<double> m = {};
  auto [min, max] = get_minmax(m);
  // cerr << min << max;
  assert(max == 0);
  assert(min == 0);
}
int main() {
  test_positive();
  test_negative();
  test_equal();
  test_one();
  test_empty();
}
