#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

struct ProcedureStep
{
    size_t amount;
    size_t from;
    size_t to;
};

size_t getFirstEmptyLineIndex(const std::vector<std::string> &lines)
{
    for (size_t i = 0; i < lines.size(); ++i)
        if (lines[i].empty())
            return i;
    return lines.size();
}

std::vector<std::string> split(const std::string &line, char delimiter)
{
    std::vector<std::string> result;
    std::stringstream ss(line);
    std::string word;

    while (getline(ss, word, delimiter))
        result.push_back(word);

    return result;
}

std::vector<std::string> parseLinesFromFile(const std::string &file_path)
{
    std::ifstream file(file_path);
    if (!file.is_open())
        throw std::runtime_error("Could not open file " + file_path);

    std::vector<std::string> lines;
    for (std::string line; std::getline(file, line);)
        lines.push_back(line);
    return lines;
}

std::vector<std::stack<char>> parseStacksFromLines(const std::vector<std::string> &lines)
{
    std::vector<std::stack<char>> stacks;
    size_t first_empty_line_index = getFirstEmptyLineIndex(lines);

    for (size_t index = 1; index < lines.front().size(); index += 4)
    {
        std::stack<char> stack;
        for (int line_index = first_empty_line_index - 2; line_index >= 0; --line_index)
            if (lines[line_index][index] >= 'A' && lines[line_index][index] <= 'Z')
                stack.push(lines[line_index][index]);
        stacks.push_back(stack);
    }

    return stacks;
}

std::vector<ProcedureStep> parseProcedureFromLines(const std::vector<std::string> &lines)
{
    std::vector<ProcedureStep> procedure;
    size_t first_empty_line_index = getFirstEmptyLineIndex(lines);

    for (size_t line_index = first_empty_line_index + 1; line_index < lines.size(); ++line_index)
    {
        std::vector<std::string> words = split(lines[line_index], ' ');
        procedure.push_back({std::stoull(words[1]), std::stoull(words[3]), std::stoull(words[5])});
    }

    return procedure;
}

void applyProcedureToStacks(std::vector<std::stack<char>> &stacks, const std::vector<ProcedureStep> &procedure)
{
    for (auto &step : procedure)
    {
        std::stack<char> &from_stack = stacks[step.from - 1];
        std::stack<char> &to_stack = stacks[step.to - 1];

        for (size_t i = 0; i < step.amount; ++i)
        {
            to_stack.push(from_stack.top());
            from_stack.pop();
        }
    }
}

std::string getTopValuesAsString(const std::vector<std::stack<char>> &stacks)
{
    std::string result;
    for (auto &stack : stacks)
        result += stack.top();
    return result;
}

std::string partOne(const std::vector<std::string> &lines)
{
    auto stacks = parseStacksFromLines(lines);
    auto procedure = parseProcedureFromLines(lines);
    applyProcedureToStacks(stacks, procedure);
    return getTopValuesAsString(stacks);
}

int main()
{
    auto lines = parseLinesFromFile("input.txt");

    std::cout << partOne(lines) << std::endl;

    return 0;
}