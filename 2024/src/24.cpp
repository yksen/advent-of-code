#include <algorithm>
#include <aoc/input.hpp>
#include <aoc/utils.hpp>
#include <array>
#include <bit>
#include <format>
#include <map>
#include <print>
#include <set>
#include <string>
#include <tuple>
#include <utility>

int count_wire(const std::map<std::string, bool>& regs, char c) {
  return std::count_if(regs.begin(), regs.end(), [c](auto p) { return p.first[0] == c; });
}

uint64_t parse_bits(const std::map<std::string, bool>& regs, char c) {
  std::string res{};
  for (auto [k, v] : regs)
    if (k[0] == c) res += std::to_string(v);
  std::reverse(res.begin(), res.end());
  return std::stoll(res, nullptr, 2);
}

auto simulate(std::map<std::string, bool> regs, std::vector<std::array<std::string, 4>> wires, int target_z) {
  for (int i{0}; target_z != count_wire(regs, 'z'); ++i) {
    if (i >= wires.size()) i = 0;
    const auto& [l, op, r, out]{wires[i]};
    if (!regs.contains(l) || !regs.contains(r)) continue;
    if (op == "AND") regs[out] = regs[l] & regs[r];
    if (op == "OR") regs[out] = regs[l] | regs[r];
    if (op == "XOR") regs[out] = regs[l] ^ regs[r];
  }
  return std::make_pair(regs, wires);
}

int main(int argc, char** argv) {
  auto input{aoc::fetch_input(argc, argv)};
  int row{0};
  std::vector<std::array<std::string, 4>> wires;
  std::map<std::string, bool> regs;
  for (; !input[row].empty(); ++row) {
    auto strs{aoc::split(input[row])};
    regs[strs[0].substr(0, strs[0].size() - 1)] = std::stoi(strs[1]);
  }
  ++row;
  for (int i{row}; i < input.size(); ++i) {
    const auto strs{aoc::split(input[i])};
    const auto l{strs[0]}, op{strs[1]}, r{strs[2]}, out{strs[4]};
    wires.push_back({l, op, r, out});
  }
  const auto target_z{std::count_if(wires.begin(), wires.end(), [](auto w) { return w[3][0] == 'z'; })};

  std::tie(regs, wires) = simulate(regs, wires, target_z);
  std::println("{}", parse_bits(regs, 'z'));

  std::vector<std::array<std::string, 4>> z_swaps, xy_swaps;
  for (auto w : wires) {
    auto [l, op, r, out]{w};
    if (out[0] == 'z' && out != "z" + std::to_string(target_z - 1) && op != "XOR") z_swaps.emplace_back(w);
    if (out[0] != 'z' && !((l[0] == 'y' && r[0] == 'x') || (l[0] == 'x' && r[0] == 'y')) && op == "XOR")
      xy_swaps.emplace_back(w);
  }

  const auto sum{parse_bits(regs, 'x') + parse_bits(regs, 'y')};
  const auto carry{std::to_string(std::countr_zero(sum ^ parse_bits(regs, 'z')))};
  std::set<std::string> swaps;
  for (auto w : wires) {
    auto [l, op, r, out]{w};
    if (l.ends_with(carry) && r.ends_with(carry)) swaps.emplace(out);
  }

  for (int i{0}; i < z_swaps.size(); ++i) swaps.insert({z_swaps[i][3], xy_swaps[i][3]});
  for (auto s : swaps) std::print("{},", s);
  std::println();
}
