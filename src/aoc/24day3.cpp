#include <regex>

#include "common.h"
#include "io.h"

/**
 * Given a line of corrupted memory, compute all `mul(x, y)` products and
 * return the sum of products.
 */
int sum_mul(const std::string& line)
{
    const std::regex re("mul\\((\\d+),(\\d+)\\)");
    const std::sregex_iterator begin(line.begin(), line.end(), re);
    const std::sregex_iterator end;

    int sum = 0;
    for (std::sregex_iterator it = begin; it != end; ++it) {
        const auto m = *it;
        assert(m.size() == 3);
        // submatches are `mul(x,y)`, `x`, and `y`

        const auto x_str = m[1].str();
        assert(x_str.size() <= 3);
        const int x = std::stoi(x_str);

        const auto y_str = m[2].str();
        assert(y_str.size() <= 3);
        const int y = std::stoi(y_str);

        sum += x * y;
    }

    return sum;
}

/**
 * Given a line of corrupted memory, split by each time `do()` or `don't()` is
 * encountered. Returns a list of `(bool enabled, string subsequence)` where
 * `enabled` means that the corresponding `subsequence` string has `mul`
 * instructions enabled.
 */
std::vector<std::pair<bool, std::string>> split_mul_enabled(std::string line)
{
    // list containing (enabled, subsequence)
    std::vector<std::pair<bool, std::string>> ret;

    bool enabled = true;  // at beginning, `mul` are enabled

    const std::regex re("do\\(\\)|don't\\(\\)");
    std::smatch m;
    while (std::regex_search(line, m, re)) {
        // prefix corresponds to previous `subsequence`
        ret.emplace_back(enabled, m.prefix());

        if (m.str().size() == 4) {  // do()
            enabled = true;
        } else {  // don't()
            enabled = false;
        }

        line = m.suffix().str();
    }

    // remaining part of the line
    ret.emplace_back(enabled, line);

    return ret;
}

void part1(const std::string& line)
{
    const int sum = sum_mul(line);
    printf("Day 3 Part 1: %d\n", sum);
}

void part2(const std::string& line)
{
    int sum = 0;
    const auto enabled_subsequence_pairs = split_mul_enabled(line);
    for (const auto& [enabled, subsequence] : enabled_subsequence_pairs) {
        if (enabled) {
            sum += sum_mul(subsequence);
        }
    }
    printf("Day 3 Part 2: %d\n", sum);
}

int main(int argc, char** argv)
{
    assert(argc == 2);
    const char* filename = argv[1];

    // concatenate file to a single line
    std::string line;
    {
        const auto lines = aoc::read_lines(filename);
        for (const auto& l : lines) {
            line += l;
        }
    }

    part1(line);
    part2(line);

    return 0;
}
