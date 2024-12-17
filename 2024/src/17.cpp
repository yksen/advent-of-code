#include <aoc/input.hpp>
#include <aoc/utils.hpp>
#include <cmath>
#include <print>
#include <string>
#include <vector>

int main(int argc, char **argv) {
  auto input{aoc::fetch_input(argc, argv)};
  std::vector<int64_t> registers, program;
  bool parse_registers{true};
  for (auto line : input) {
    if (line.empty()) {
      parse_registers = false;
      continue;
    }
    if (parse_registers)
      registers.emplace_back(aoc::get_numbers(line).front());
    else
      for (auto n : aoc::get_numbers(line)) program.emplace_back(n);
  }

  std::map<int, int64_t *> combo{{1, new int64_t{1}}, {2, new int64_t{2}}, {3, new int64_t{3}},
                                 {4, &registers[0]},  {5, &registers[1]},  {6, &registers[2]}};
  int64_t reg_init{-1};
  std::string output{};

  auto join_vector{[](auto vec) {
    std::string res{};
    for (auto v : vec) res += std::to_string(v) + ',';
    return res;
  }};
  const std::string program_str{join_vector(program)};

  bool skip{false};
  while (output != program_str) {
    ++reg_init;
    output = "";
    registers = {reg_init, 0, 0};
    skip = false;
    for (int i{0}; i < program.size(); i += 2) {
      const auto opcode{program[i]}, operand{program[i + 1]};
      switch (opcode) {
        case 0:  // adv
          registers[0] = registers[0] / (1 << *combo[operand]);
          break;
        case 1:  // bxl
          registers[1] ^= operand;
          break;
        case 2:  // bst
          registers[1] = *combo[operand] % 8;
          break;
        case 3:  // jnz
          if (registers[0] != 0) i = operand - 2;
          break;
        case 4:  // bxc
          registers[1] ^= registers[2];
          break;
        case 5:  // out
          output += std::to_string(*combo[operand] % 8) + ',';
          if (output.size() > program_str.size() ||
              output[output.size() - 2] != program_str[output.size() - 2])
            skip = true;
          break;
        case 6:  // bdv
          registers[1] = registers[0] / (1 << *combo[operand]);
          break;
        case 7:  // cdv
          registers[2] = registers[0] / (1 << *combo[operand]);
          break;
      }
      if (skip) break;
    }
  }

  std::println("{}", reg_init);
}
