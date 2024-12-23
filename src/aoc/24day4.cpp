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
    // we just do brute force: we iterate over all starting positions (x, y)
    // and try to find "XMAS" in all 8 directions.

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

void part2(const Puzzle& puzzle)
{
    // we iterate over all possible positions of the center "A". if we look at
    // the four corners of the "X-MAS" in clockwise order, we should see a
    // permutation of "MMSS".

    static const std::array<std::array<int, 2>, 4> DIRECTIONS = {{
        {1, 1},
        {-1, 1},
        {-1, -1},
        {1, -1},
    }};

    /**
     * Returns true if (x, y) is the center of an "X-MAS".
     */
    auto search = [&](int x, int y) -> bool {
        if (x <= 0 || x >= puzzle.ncols - 1 || y <= 0 || y >= puzzle.nrows - 1) {
            return false;
        }
        if (puzzle.at(x, y) != 'A') {
            return false;
        }

        std::vector<char> corners(4);
        for (int i = 0; i < corners.size(); ++i) {
            const auto& dir = DIRECTIONS[i];
            corners[i] = puzzle.at(x + dir[0], y + dir[1]);
        }

        // need two "M" and two "S"
        {
            int num_m = 0;
            int num_s = 0;
            for (char c : corners) {
                if (c == 'M') {
                    ++num_m;
                } else if (c == 'S') {
                    ++num_s;
                }
            }

            if (num_m != 2 || num_s != 2) {
                return false;
            }
        }

        // we count the number of "M -> S" or "S -> M" switches in `corners`.
        // if it is a permutation of "MMSS", we should only have 2 switches.
        // otherwise, e.g. for "MSMS", there will be 4 switches.
        {
            int num_switches = 0;
            char prev = corners[3];
            for (char c : corners) {
                if (c != prev) {
                    ++num_switches;
                }
                prev = c;
            }

            assert(num_switches == 2 || num_switches == 4);
            if (num_switches == 4) {
                return false;
            }
        }

        return true;
    };

    int count = 0;

    // do breadth-first search
    for (int x = 1; x < puzzle.ncols - 1; ++x) {
        for (int y = 1; y < puzzle.nrows - 1; ++y) {
            if (search(x, y)) {
                ++count;
            }
        }
    }

    printf("Day 4 Part 2: %d\n", count);
}


int main(int argc, char** argv)
{
    assert(argc == 2);
    const char* filename = argv[1];

    const Puzzle puzzle(filename);

    part1(puzzle);
    part2(puzzle);

    return 0;
}
