#include <aoc/input.hpp>
#include <aoc/utils.hpp>
#include <iterator>
#include <optional>
#include <print>
#include <span>
#include <string>
#include <vector>

std::optional<int64_t> run(const std::span<int> program, int &i, std::map<int, int64_t> &combo,
                           bool ignore_adv = false) {
  const auto opcode{program[i]}, operand{program[i + 1]};
  switch (opcode) {
    case 0:  // adv
      if (!ignore_adv) combo[4] = combo[4] >> combo[operand];
      break;
    case 1:  // bxl
      combo[5] ^= operand;
      break;
    case 2:  // bst
      combo[5] = combo[operand] % 8;
      break;
    case 3:  // jnz
      if (combo[4] != 0) i = operand - 2;
      break;
    case 4:  // bxc
      combo[5] ^= combo[6];
      break;
    case 5:  // out
      return combo[operand] % 8;
    case 6:  // bdv
      combo[5] = combo[4] >> combo[operand];
      break;
    case 7:  // cdv
      combo[6] = combo[4] >> combo[operand];
      break;
  }
  return {};
}

std::optional<int64_t> find(const std::vector<int> &program, std::span<int> target,
                            std::map<int, int64_t> combo, int64_t result) {
  if (target.empty()) return result;
  for (int i{0}; i < 8; ++i) {
    combo[4] = result << 3 | i;
    combo[5] = 0;
    combo[6] = 0;
    for (int j{0}; j < program.size() - 2; j += 2) {
      auto output{run(target, j, combo, true)};
      if (output && *output == target.back()) {
        auto res{find(program, std::span{target.begin(), std::prev(target.end())}, combo, combo[4])};
        if (!res) continue;
        return *res;
      }
    }
  }
  return {};
}

int main(int argc, char **argv) {
  auto input{aoc::fetch_input(argc, argv)};
  std::vector<int> program, output;
  std::map<int, int64_t> combo{{1, 1}, {2, 2}, {3, 3}};
  bool parse_registers{true};
  for (auto line : input)
    if (line.empty())
      parse_registers = false;
    else if (parse_registers)
      combo[combo.size() + 1] = aoc::get_numbers(line).front();
    else
      for (auto n : aoc::get_numbers(line)) program.emplace_back(n);

  auto join_vector{[](auto vec) {
    std::string res{};
    for (auto v : vec) res += std::to_string(v) + ',';
    return res.substr(0, res.size() - 1);
  }};

  auto c{combo};
  for (int i{0}; i < program.size(); i += 2)
    if (auto res{run(program, i, combo)}) output.emplace_back(*res);
  std::println("{} {}", join_vector(output), *find(program, program, c, 0));
}
