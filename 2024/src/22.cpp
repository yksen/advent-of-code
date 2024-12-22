#include <algorithm>
#include <aoc/input.hpp>
#include <map>
#include <numeric>
#include <print>
#include <string>
#include <tuple>
#include <utility>

using Seq = std::tuple<int, int, int, int>;
const int64_t pruning_number{16777216};

int main(int argc, char** argv) {
  auto input{aoc::fetch_input(argc, argv)};
  std::vector<std::vector<int64_t>> buyers(input.size(), std::vector<int64_t>());
  for (int i{0}; i < input.size(); ++i) buyers[i].emplace_back(std::stoi(input[i]));

  for (int i{0}; i < 2000; ++i)
    for (auto& prices : buyers) {
      prices.emplace_back(prices.back());
      int64_t a{prices.back() * 64};
      prices.back() ^= a;
      prices.back() %= pruning_number;
      int64_t b{prices.back() / 32};
      prices.back() ^= b;
      prices.back() %= pruning_number;
      int64_t c{prices.back() * 2048};
      prices.back() ^= c;
      prices.back() %= pruning_number;
    }

  std::println("{}", std::accumulate(buyers.begin(), buyers.end(), 0ll,
                                     [](int64_t sum, auto& prices) { return sum + prices.back(); }));

  for (auto& prices : buyers)
    for (auto& price : prices) price %= 10;

  std::map<Seq, std::pair<int64_t, bool>> seqs;
  for (auto prices : buyers) {
    auto d{prices};
    std::adjacent_difference(d.begin(), d.end(), d.begin());
    for (auto& [_, v] : seqs) v.second = true;
    for (int i{1}; i < d.size() - 4; ++i) {
      Seq seq{d[i], d[i + 1], d[i + 2], d[i + 3]};
      if (!seqs.contains(seq))
        seqs[seq] = {prices[i + 3], false};
      else if (seqs[seq].second)
        seqs[seq] = {seqs[seq].first + prices[i + 3], false};
    }
  }

  std::println("{}", std::max_element(seqs.begin(), seqs.end(), [](auto l, auto r) {
                       return l.second < r.second;
                     })->second.first);
}
