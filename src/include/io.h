#pragma once

#include <cassert>
#include <fstream>
#include <string>
#include <vector>

namespace aoc
{

/**
 * Read lines from a text file.
 */
std::vector<std::string> read_lines(const char* filename)
{
    std::fstream f(filename);
    std::vector<std::string> lines;

    std::string line;
    while (getline(f, line)) {
        lines.push_back(std::move(line));
    }

    f.close();
    return lines;
}

/**
 * Split the string `str` using the separator `sep`.
 */
std::vector<std::string> split(const std::string& str, const std::string& sep)
{
    assert(sep.size() > 0);
    std::vector<std::string> parts;

    std::string::size_type start = 0;
    std::string::size_type end = str.find(sep, start);
    while (end != std::string::npos) {
        parts.emplace_back(str.substr(start, end - start));
        start = end + sep.size();
        end = str.find(sep, start);
    }
    parts.emplace_back(str.substr(start));

    return parts;
}

/**
 * Convert vector of strings into vector of integers.
 */
std::vector<int> stoi(const std::vector<std::string>& strs)
{
    std::vector<int> ints(strs.size());
    for (int i = 0; i < strs.size(); ++i) {
        ints[i] = std::stoi(strs[i]);
    }
    return ints;
}

}  // namespace aoc
