#include <algorithm>
#include <aoc/utils.hpp>
#include <iostream>
#include <iterator>
#include <map>
#include <print>
#include <set>
#include <sstream>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> input_rules;
  std::vector<std::string> input_steps;
  std::string line;
  while (std::getline(std::cin, line) && !line.empty()) input_rules.push_back(line);
  while (std::getline(std::cin, line) && !line.empty()) input_steps.push_back(line);

  std::map<int, std::set<int>> rules;
  std::vector<std::vector<int>> rounds;
  for (auto rule : input_rules) {
    std::replace(rule.begin(), rule.end(), '|', ' ');
    std::stringstream stream{rule};
    int lhs, rhs;
    stream >> lhs >> rhs;
    if (rules.contains(lhs))
      rules.at(lhs).insert(rhs);
    else
      rules[lhs] = {rhs};
  }
  for (auto steps_string : input_steps) {
    rounds.emplace_back();
    std::replace(steps_string.begin(), steps_string.end(), ',', ' ');
    std::stringstream stream{steps_string};
    int val;
    while (stream >> val) rounds.back().push_back(val);
  }

  int sum{0}, corrected_sum{0};
  for (auto pages : rounds) {
    bool valid{true};
    for (int i{0}; i < pages.size(); ++i) {
      auto page{pages.at(i)};
      bool before{std::all_of(pages.begin(), pages.begin() + i, [&](auto val) {
        return (rules.contains(val))
                   ? std::find(rules.at(val).begin(), rules.at(val).end(), page) != rules.at(val).end()
                   : false;
      })};
      bool after{std::all_of(pages.begin() + i + 1, pages.end(), [&](auto val) {
        return (rules.contains(page))
                   ? std::find(rules.at(page).begin(), rules.at(page).end(), val) != rules.at(page).end()
                   : true;
      })};

      if (!before || !after) {
        valid = false;

        std::map<int, int> rules_count;
        std::sort(pages.begin(), pages.end());
        std::for_each(pages.begin(), pages.end(), [&](auto val) {
          if (rules.contains(val)) {
            std::vector<int> intersection;
            std::set_intersection(pages.begin(), pages.end(), rules.at(val).begin(), rules.at(val).end(),
                                  std::back_inserter(intersection));
            rules_count[val] = intersection.size();
          } else {
            rules_count[val] = 0;
          }
        });

        corrected_sum += std::find_if(rules_count.begin(), rules_count.end(), [&](auto k) {
                           return k.second == pages.size() / 2;
                         })->first;
        break;
      }
    }
    if (valid) sum += pages.at(pages.size() / 2);
  }

  std::print("{} {}\n", sum, corrected_sum);
}
