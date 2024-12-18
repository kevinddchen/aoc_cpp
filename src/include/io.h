#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace aoc
{

/**
 * Read lines from a text file.
 */
std::vector<std::string> read_lines(const std::string& filename)
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

}  // namespace aoc
