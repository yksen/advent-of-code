#include <algorithm>
#include <aoc/input.hpp>
#include <print>
#include <string>
#include <utility>
#include <vector>

int64_t last_file_pos(const std::vector<int64_t>& ids) {
  return std::distance(std::find_if(ids.rbegin(), ids.rend(), [](int64_t val) { return val != -1; }),
                       ids.rend()) -
         1;
}

int64_t part1(std::vector<int64_t> ids) {
  int64_t checksum{0};
  for (size_t i{0}; i < ids.size(); ++i) {
    if (ids[i] != -1) continue;
    auto pos{last_file_pos(ids)};
    if (i > pos) break;
    ids[i] = ids[pos];
    ids[pos] = -1;
  }

  for (size_t i{0}; i <= last_file_pos(ids); ++i) checksum += i * ids[i];
  return checksum;
}

std::pair<int64_t, int64_t> first_chunk(const auto& range, size_t offset = 0, const int64_t val = -1) {
  auto begin_it{std::find(std::next(range.begin(), offset), range.end(), val)};
  if (begin_it == range.end()) return {-1, -1};
  int64_t begin{std::distance(range.begin(), begin_it)};
  int64_t end{begin};
  while (end + 1 < range.size() && range[end + 1] == val) ++end;
  return {begin, end};
}

int64_t part2(std::vector<int64_t> ids) {
  std::vector<int64_t> unique{ids};
  auto last{std::unique(unique.begin(), unique.end())};
  unique.erase(last, unique.end());
  unique.erase(std::remove(unique.begin(), unique.end(), -1), unique.end());

  for (int64_t i{static_cast<int64_t>(unique.size() - 1)}; i >= 0; --i) {
    const auto file_chunk{first_chunk(ids, 0, unique.at(i))};
    auto free_chunk{first_chunk(ids)};
    while (file_chunk.second - file_chunk.first > free_chunk.second - free_chunk.first &&
           free_chunk.first < file_chunk.second) {
      free_chunk = first_chunk(ids, free_chunk.second + 1);
    }
    if (free_chunk.first >= file_chunk.second) continue;
    for (auto j{0}; j <= file_chunk.second - file_chunk.first; ++j) {
      ids.at(free_chunk.first + j) = ids.at(file_chunk.first + j);
      ids.at(file_chunk.first + j) = -1;
    }
  }

  int64_t checksum{0};
  for (size_t i{0}; i < ids.size(); ++i)
    if (ids.at(i) != -1) checksum += i * ids[i];
  return checksum;
}

int main(int argc, char** argv) {
  auto input{aoc::fetch_input(argc, argv).front()};
  int64_t id{0};
  bool is_file{true};

  std::vector<int64_t> ids;

  for (const char c : input) {
    if (is_file) {
      std::vector tmp(c - '0', id);
      ids.insert(ids.end(), tmp.begin(), tmp.end());
      ++id;
    } else {
      std::vector tmp(c - '0', -1);
      ids.insert(ids.end(), tmp.begin(), tmp.end());
    }
    is_file = !is_file;
  }

  std::print("{} {}\n", part1(ids), part2(ids));
}
