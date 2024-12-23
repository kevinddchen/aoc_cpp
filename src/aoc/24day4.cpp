#include <array>

#include "common.h"
#include "io.h"

/**
 * Data structure holding the word search puzzle.
 */
struct Puzzle {
    std::vector<std::vector<char>> puzzle;
    int nrows;
    int ncols;

    Puzzle(const char* filename)
    {
        const auto lines = aoc::read_lines(filename);

        nrows = lines.size();
        puzzle.reserve(nrows);
        assert(nrows > 0);
        ncols = lines[0].size();

        for (int i = 0; i < nrows; ++i) {
            const auto& line = lines[i];
            assert(line.size() == ncols);
            puzzle.emplace_back(line.begin(), line.end());
        }
    }

    char at(int x, int y) const { return puzzle[y][x]; }

    void print() const
    {
        for (int y = 0; y < nrows; ++y) {
            for (int x = 0; x < ncols; ++x) {
                printf("%c", at(x, y));
            }
            printf("\n");
        }
    }
};

void part1(const Puzzle& puzzle)
{
    static const std::array<char, 4> KEYWORD = {{'X', 'M', 'A', 'S'}};
    static const std::array<std::array<int, 2>, 8> DIRECTIONS = {{
        {1, 0},
        {1, 1},
        {0, 1},
        {-1, 1},
        {-1, 0},
        {-1, -1},
        {0, -1},
        {1, -1},
    }};

    /**
     * Returns true if we can find "XMAS" starting at (x, y) going in direction (dx, dy).
     */
    auto search = [&](int x, int y, int dx, int dy) -> bool {
        for (auto c : KEYWORD) {
            if (x < 0 || x >= puzzle.ncols || y < 0 || y >= puzzle.nrows) {
                return false;
            }
            if (puzzle.at(x, y) != c) {
                return false;
            }
            x += dx;
            y += dy;
        }
        return true;
    };

    int count = 0;

    // do breadth-first search
    for (int x = 0; x < puzzle.ncols; ++x) {
        for (int y = 0; y < puzzle.nrows; ++y) {
            for (const auto& dir : DIRECTIONS) {
                if (search(x, y, dir[0], dir[1])) {
                    ++count;
                }
            }
        }
    }

    printf("Day 4 Part 1: %d\n", count);
}


int main(int argc, char** argv)
{
    assert(argc == 2);
    const char* filename = argv[1];

    const Puzzle puzzle(filename);
    // puzzle.print();

    part1(puzzle);

    return 0;
}
