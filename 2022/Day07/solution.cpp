#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

const uint64_t MAX_TOTAL_DIRECTORY_SIZE = 100'000;
const uint64_t TOTAL_DISK_SPACE = 70'000'000;
const uint64_t MIN_UNUSED_SPACE = 30'000'000;

static uint64_t smallest_candidate_directory_size;

std::vector<std::string> splitString(const std::string &str, const char &delimiter)
{
    std::vector<std::string> chunks;
    std::stringstream ss(str);
    std::string chunk;
    while (std::getline(ss, chunk, delimiter))
        chunks.push_back(chunk);
    return chunks;
}

std::vector<std::string> readLinesFromFile(const std::string &file_path)
{
    std::ifstream file(file_path);
    std::vector<std::string> lines;
    for (std::string line; std::getline(file, line);)
        lines.push_back(line);
    return lines;
}

uint64_t searchDepthAndSumSizes(const std::vector<std::string> &lines, size_t &i, uint64_t &total_size, uint64_t space_needed)
{
    uint64_t directory_size = 0;
    while (i < lines.size() - 1)
    {
        ++i;
        auto line = lines[i];
        auto chunks = splitString(line, ' ');

        if (chunks[0] != "$" && chunks[0] != "dir")
            directory_size += std::stoull(chunks[0]);
        else if (chunks[0] == "$")
        {
            if (chunks[1] == "ls")
                continue;
            else if (chunks[2] == "..")
            {
                if (directory_size <= MAX_TOTAL_DIRECTORY_SIZE)
                    total_size += directory_size;
                if (directory_size >= space_needed && directory_size < smallest_candidate_directory_size)
                    smallest_candidate_directory_size = directory_size;
                return directory_size;
            }
            else
                directory_size += searchDepthAndSumSizes(lines, i, total_size, space_needed);
        }
    }

    if (directory_size < MAX_TOTAL_DIRECTORY_SIZE)
        total_size += directory_size;
    if (directory_size >= space_needed && directory_size < smallest_candidate_directory_size)
        smallest_candidate_directory_size = directory_size;
    return directory_size;
}

std::pair<uint64_t, uint64_t> partOne(const std::vector<std::string> &lines)
{
    size_t index = 0;
    uint64_t sum_of_directory_sizes = 0;
    uint64_t total_size = searchDepthAndSumSizes(lines, index, sum_of_directory_sizes, 0);

    return {sum_of_directory_sizes, total_size};
}

uint64_t partTwo(const std::vector<std::string> &lines, uint64_t total_size)
{
    size_t index = 0;
    uint64_t sum_of_directory_sizes = 0;
    uint64_t space_needed = MIN_UNUSED_SPACE - (TOTAL_DISK_SPACE - total_size);

    smallest_candidate_directory_size = MIN_UNUSED_SPACE;
    searchDepthAndSumSizes(lines, index, sum_of_directory_sizes, space_needed);

    return smallest_candidate_directory_size;
}

int main()
{
    auto lines = readLinesFromFile("input.txt");

    auto [sum_of_directory_sizes, total_size] = partOne(lines);
    auto smallest_directory_size = partTwo(lines, total_size);

    std::cout << sum_of_directory_sizes << std::endl;
    std::cout << smallest_directory_size << std::endl;
}
