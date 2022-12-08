#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

const uint64_t MAX_TOTAL_DIRECTORY_SIZE = 1'000'00;

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

uint64_t searchDepthAndSumSizes(const std::vector<std::string> &lines, size_t &i, uint64_t &total_size)
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
                if (directory_size < MAX_TOTAL_DIRECTORY_SIZE)
                    total_size += directory_size;
                return directory_size;
            }
            else
                directory_size += searchDepthAndSumSizes(lines, i, total_size);
        }
    }

    if (directory_size < MAX_TOTAL_DIRECTORY_SIZE)
        total_size += directory_size;
    return directory_size;
}

uint64_t partOne(const std::vector<std::string> &lines)
{
    size_t index = 0;
    uint64_t total_size = 0;
    searchDepthAndSumSizes(lines, index, total_size);
    return total_size;
}

int main()
{
    auto lines = readLinesFromFile("input.txt");

    std::cout << partOne(lines) << std::endl;
}
