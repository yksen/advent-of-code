#include <algorithm>
#include <aoc/utils.hpp>
#include <print>
#include <regex>
#include <sstream>
#include <string>

int main() {
  const std::regex pattern{R"((mul\(\d{1,3},\d{1,3}\)|do\(\)|don't\(\)))"};
  const std::string instruction{"mul"};

  std::string input{}, line{};
  while (std::getline(std::cin, line) && !line.empty()) input += line;
  bool active{true};
  int sum{0};

  for (std::sregex_iterator it{input.begin(), input.end(), pattern}, end{}; it != end; ++it) {
    std::string match{std::smatch{*it}.str()};
    if (match == "don't()") {
      active = false;
      continue;
    }
    if (match == "do()") {
      active = true;
      continue;
    }
    if (!active) continue;
    std::replace(match.begin(), match.end(), ',', ' ');
    std::stringstream stream{
        match.substr(instruction.size() + 1, match.size() - (instruction.size() + 2)).data()};
    int a, b;
    stream >> a >> b;
    sum += a * b;
  }

  std::print("{}\n", sum);
}
