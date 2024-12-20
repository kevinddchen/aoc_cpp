#include <regex>

#include "common.h"
#include "io.h"

/**
 * Given a line of corrupted memory, compute all `mul(x, y)` products and
 * return the sum of products.
 */
int parse_mul(const std::string& line)
{
    const std::regex re("mul\\((\\d+),(\\d+)\\)");
    const std::sregex_iterator begin(line.begin(), line.end(), re);
    const std::sregex_iterator end;

    int sum = 0;
    for (std::sregex_iterator it = begin; it != end; ++it) {
        const auto match = *it;
        assert(match.size() == 3);
        // submatches are `mul(x,y)`, `x`, and `y`

        const auto x_str = match[1].str();
        assert(x_str.size() <= 3);
        const int x = std::stoi(x_str);

        const auto y_str = match[2].str();
        assert(y_str.size() <= 3);
        const int y = std::stoi(y_str);

        sum += x * y;
    }

    return sum;
}

void part1(const std::vector<std::string>& lines)
{
    int sum = 0;
    for (const auto& line : lines) {
        sum += parse_mul(line);
    }
    printf("Day 2 Part 1: %d\n", sum);
}

int main(int argc, char** argv)
{
    assert(argc == 2);
    const char* filename = argv[1];

    const auto lines = aoc::read_lines(filename);

    part1(lines);

    return 0;
}
