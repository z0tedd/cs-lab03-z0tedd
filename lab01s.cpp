#include "histogram.h"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>
using namespace std;
vector<double> get_numbers(size_t number_count) {
  vector<double> numbers(number_count);
  for_each(numbers.begin(), numbers.end(), [](auto &x) { cin >> x; });
  return numbers;
}
vector<size_t> make_histogram(size_t bin_count, const vector<double> &numbers) {
  size_t number_count = numbers.size();
  vector<size_t> bins(bin_count);
  auto [Min, Max] = get_minmax(numbers);
  double bin_size = (Max - Min) / bin_count;
  for (size_t i = 0; i < number_count; i++) {
    bool found = false;
    for (size_t j = 0; !found && (j < bin_count - 1); j++) {
      auto low_bound = Min + j * bin_size;
      auto upp_bound = Min + (j + 1) * bin_size;
      if ((low_bound <= numbers[i]) && (numbers[i] < upp_bound)) {
        bins[j]++;
        found = true;
      }
    }
    if (!found) {
      bins[bin_count - 1]++;
    }
  }

  return bins;
}
void show_histogram_text(const vector<size_t> &bins) {
  auto [min_count, max_count] = get_minmax(bins);
  bool isScalable = false;
  if (max_count > 76) {
    isScalable = true;
  }
  const size_t SCREEN_WIDTH = 80;
  const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
  for (auto count : bins) {
    if (count <= 99)
      cout << ' ';
    if (count <= 9)
      cout << ' ';
    cout << count << "|";
    size_t height = count;
    if (isScalable) {
      height = MAX_ASTERISK * (static_cast<double>(count) / max_count);
      if (count == max_count) {
        height = 76;
      }
    }
    cerr << height;
    for (int i = 0; i < height; i++) {
      cout << '*';
    }
    cout << '\n';
  }
}
void svg_begin(double width, double height) {
  cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
  cout << "<svg ";
  cout << "width='" << width << "' ";
  cout << "height='" << height << "' ";
  cout << "viewBox='0 0 " << width << " " << height << "' ";
  cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end() { cout << "</svg>\n"; }

void svg_text(double left, double baseline, string text) {
  cout << "<text x='" << left << "' y='" << baseline << "'>" << text
       << "</text>";
}
void svg_rect(double x, double y, double width, double height,
              string stroke = "black", string fill = "black") {
  cout << "<rect x='" << x << "' y ='" << y << "' width ='" << width
       << "' height='" << height << "' stroke ='" << stroke << "' fill ='"
       << fill << "'></rect>";
}
void show_histogram_svg(const vector<size_t> &bins) {
  const auto IMAGE_WIDTH = 400;
  const auto IMAGE_HEIGHT = 300;
  const auto TEXT_LEFT = 20;
  const auto TEXT_BASELINE = 20;
  const auto TEXT_WIDTH = 60; // Раньше было 50
  const auto BIN_HEIGHT = 30;
  const auto BLOCK_WIDTH = 10;
  svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
  double top = 0;

  auto [min_count, max_count] = get_minmax(bins);
  bool isScalable = false;
  if (max_count * BLOCK_WIDTH > IMAGE_WIDTH) {
    isScalable = true;
  }
  const size_t SCREEN_WIDTH = IMAGE_WIDTH;
  const size_t MAX_ASTERISK = SCREEN_WIDTH - TEXT_WIDTH;

  // for (size_t bin : bins) {
  //   const double bin_width = BLOCK_WIDTH * bin;
  //   svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
  //   svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
  //   top += BIN_HEIGHT;
  // }

  for (size_t bin : bins) {

    double height = bin * BLOCK_WIDTH;
    if (isScalable) {
      height = MAX_ASTERISK * (static_cast<double>(bin) / max_count);
      if (bin == max_count) {
        height = MAX_ASTERISK;
      }
    }
    cerr << '\n' << height;
    // double bin_width = BLOCK_WIDTH * height; // раньше был конст, но я это
    // убрал
    //  В теории это вообще быть не должно, просто меня бесит не форматированный
    //  текст
    auto TEXT_ALIGN = 0;
    if (bin <= 99)
      TEXT_ALIGN += BLOCK_WIDTH;
    if (bin <= 9)
      TEXT_ALIGN += BLOCK_WIDTH;

    svg_text(TEXT_LEFT + TEXT_ALIGN, top + TEXT_BASELINE, to_string(bin));
    svg_rect(TEXT_WIDTH, top, height, BIN_HEIGHT);
    top += BIN_HEIGHT;
  }
  // svg_rect(TEXT_WIDTH, 0, bins[0] * BLOCK_WIDTH, BIN_HEIGHT);
  // svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bins[0]));
  svg_end();
}
int main() {

  size_t number_count;
  cerr << "Enter number count: ";
  cin >> number_count;
  size_t bin_count;
  const vector<double> numbers =
      get_numbers(number_count); // const ломает программу
  cerr << "Enter bin count: ";
  cin >> bin_count;
  const auto bins = make_histogram(bin_count, numbers);
  // auto it = minmax_element(numbers.begin(), numbers.end());
  // double Min = *(it.first), Max = *(it.second);

  show_histogram_svg(bins);
  return 0;
}
