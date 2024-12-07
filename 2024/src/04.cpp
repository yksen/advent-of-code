#include <aoc/input.hpp>
#include <aoc/utils.hpp>
#include <print>
#include <string>
#include <string_view>
#include <vector>

int count_substrs(const std::vector<std::string>& input, const std::string_view substr) {
  int sum{0};
  for (auto line : input) sum += aoc::find_all_substr(line, substr).size();
  return sum;
}

std::vector<std::string> get_diagonals(const std::vector<std::string>& rows) {
  std::vector<std::string> diagonals{(rows.front().size() * 2 - 1) * 2};
  for (auto y{0}; y < rows.at(0).size(); ++y) {
    const auto row{rows.at(y)};
    for (auto x{0}; x < row.size(); ++x) {
      diagonals.at(y - x + row.size() - 1) += row.at(x);
      diagonals.at(y + x + row.size() * 2 - 1) += row.at(x);
    }
  }
  return diagonals;
}

int main() {
  const std::vector<std::string> words{"XMAS", "SAMX"};
  const std::vector<std::string> x_words{"MAS", "SAM"};
  std::vector<std::string> rows;
  std::string line{};
  while (std::getline(std::cin, line) && !line.empty()) rows.push_back(line);
  int sum{0}, x_sum{0};

  std::vector<std::string> columns{rows.front().size()};
  std::vector<std::string> diagonals{get_diagonals(rows)};
  for (auto y{0}; y < rows.at(0).size(); ++y) {
    const auto row{rows.at(y)};
    for (auto x{0}; x < row.size(); ++x) {
      columns.at(x) += row.at(x);

      if (x == 0 || x == row.size() - 1 || y == 0 || y == rows.size() - 1) continue;
      int x_word_count{0};
      for (auto word : x_words) {
        std::vector<std::string> square{rows.at(y - 1).substr(x - 1, word.size()),
                                        row.substr(x - 1, word.size()),
                                        rows.at(y + 1).substr(x - 1, word.size())};
        const auto square_diagonals{get_diagonals(square)};
        x_word_count += count_substrs(square_diagonals, word);
      }
      if (x_word_count == 2) ++x_sum;
    }
  }

  for (auto word : words)
    sum += count_substrs(rows, word) + count_substrs(columns, word) + count_substrs(diagonals, word);

  std::print("{} {}\n", sum, x_sum);
}
