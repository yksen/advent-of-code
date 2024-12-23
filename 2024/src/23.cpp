#include <algorithm>
#include <aoc/input.hpp>
#include <aoc/utils.hpp>
#include <iterator>
#include <map>
#include <print>
#include <set>
#include <string>

std::map<std::string, std::set<std::string>> adj;

std::set<std::string> get_largest(std::set<std::string>& pcs, std::set<std::string>& conns) {
  if (pcs.empty()) return conns;

  std::set<std::string> largest{conns};
  for (auto it{pcs.begin()}; it != pcs.end();) {
    conns.insert(*it);
    std::set<std::string> inter;
    std::set_intersection(pcs.begin(), pcs.end(), adj[*it].begin(), adj[*it].end(),
                          std::inserter(inter, inter.end()));
    auto res{get_largest(inter, conns)};

    if (res.size() > largest.size()) largest = res;
    conns.erase(*it);
    it = pcs.erase(it);
  }
  return largest;
}

int main(int argc, char** argv) {
  auto input{aoc::fetch_input(argc, argv)};
  std::set<std::string> pcs;

  for (auto line : input) {
    const auto l{line.substr(0, 2)}, r{line.substr(3, 2)};
    adj[l].emplace(r);
    adj[r].emplace(l);
    pcs.insert({l, r});
  }

  std::set<std::set<std::string>> triangles;
  for (const auto& [v, neighbors] : adj) {
    for (const auto& l : neighbors) {
      std::set<std::string> common;
      for (const auto& r : neighbors)
        if (adj[r].contains(l)) common.emplace(r);
      for (const auto& c : common) triangles.insert({l, v, c});
    }
  }

  std::println("{}", std::count_if(triangles.begin(), triangles.end(), [](auto t) {
                 return std::any_of(t.begin(), t.end(), [](auto v) { return v[0] == 't'; });
               }));

  std::set<std::string> conns;
  for (const auto& pc : get_largest(pcs, conns)) std::print("{},", pc);
  std::println();
}
