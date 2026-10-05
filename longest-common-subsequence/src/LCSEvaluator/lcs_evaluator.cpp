/**********************************************************************
  Student Name: Caleb Hughes
  File Name: lcs_evaluator.cpp
  Assignment number: Project 5
  File Description: Full matrix lcs, two row length dp, pairwise
                    lengths, similarity labels, formatted table output
**********************************************************************/

#include "lcs_evaluator.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace {

inline std::size_t flatIndex(std::size_t row, std::size_t col, std::size_t totalCols) {
    return row * totalCols + col;
}

}

Part1Result evaluatePart1FullMatrix(const std::string& x, const std::string& y) {
    const std::size_t m = x.size();
    const std::size_t n = y.size();
    const std::size_t rows = m + 1;
    const std::size_t cols = n + 1;
    std::vector<int> c(rows * cols, 0);

    for (std::size_t i = 1; i < rows; ++i) {
        for (std::size_t j = 1; j < cols; ++j) {
            if (x[i - 1] == y[j - 1]) {
                c[flatIndex(i, j, cols)] = c[flatIndex(i - 1, j - 1, cols)] + 1;
            } else {
                const int up = c[flatIndex(i - 1, j, cols)];
                const int left = c[flatIndex(i, j - 1, cols)];
                c[flatIndex(i, j, cols)] = std::max(up, left);
            }
        }
    }

    const int lcsLen = c[flatIndex(m, n, cols)];
    std::string lcs;
    lcs.reserve(static_cast<std::size_t>(std::max(0, lcsLen)));

    std::size_t i = m;
    std::size_t j = n;
    while (i > 0 && j > 0) {
        if (x[i - 1] == y[j - 1]) {
            lcs.push_back(x[i - 1]);
            --i;
            --j;
        } else if (c[flatIndex(i - 1, j, cols)] >= c[flatIndex(i, j - 1, cols)]) {
            --i;
        } else {
            --j;
        }
    }
    std::reverse(lcs.begin(), lcs.end());

    Part1Result out;
    out.x = x;
    out.y = y;
    out.lcs_length = lcsLen;
    out.lcs_subsequence = std::move(lcs);
    return out;
}

int lcsLengthTwoRow(const std::string& x, const std::string& y) {
    const std::size_t m = x.size();
    const std::size_t n = y.size();
    const std::size_t cols = n + 1;
    std::vector<int> row(2 * cols, 0);

    for (std::size_t i = 1; i <= m; ++i) {
        const std::size_t cur = i & 1U;
        const std::size_t prev = cur ^ 1U;
        row[flatIndex(cur, 0, cols)] = 0;
        for (std::size_t j = 1; j < cols; ++j) {
            if (x[i - 1] == y[j - 1]) {
                row[flatIndex(cur, j, cols)] =
                    row[flatIndex(prev, j - 1, cols)] + 1;
            } else {
                row[flatIndex(cur, j, cols)] =
                    std::max(row[flatIndex(prev, j, cols)], row[flatIndex(cur, j - 1, cols)]);
            }
        }
    }
    return row[flatIndex(m & 1U, n, cols)];
}

std::vector<std::vector<int>> pairwiseLcsLengths(const std::vector<std::string>& strings) {
    const std::size_t n = strings.size();
    std::vector<std::vector<int>> table(n);
    for (std::size_t i = 0; i < n; ++i) {
        table[i].assign(n, 0);
    }
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = i + 1; j < n; ++j) {
            const int len = lcsLengthTwoRow(strings[i], strings[j]);
            table[i][j] = len;
            table[j][i] = len;
        }
    }
    return table;
}

char classifySimilarity(const std::string& a, const std::string& b, int lcs_length) {
    const double lenA = static_cast<double>(a.size());
    const double lenB = static_cast<double>(b.size());
    const double shorter = std::min(lenA, lenB);
    const double longer = std::max(lenA, lenB);
    const double lc = static_cast<double>(lcs_length);

    if (longer <= 0.0) {
        return 'H';
    }
    if (shorter <= 0.0) {
        return 'D';
    }

    const double lengthRatio = shorter / longer;
    const double lcsRatio = lc / shorter;

    const bool high = (lengthRatio >= 0.90) && (lcsRatio >= 0.90);
    const bool medium = (lengthRatio >= 0.80) && (lcsRatio >= 0.80);
    const bool low = (lengthRatio >= 0.60) && (lcsRatio >= 0.50);

    if (high) {
        return 'H';
    }
    if (medium) {
        return 'M';
    }
    if (low) {
        return 'L';
    }
    return 'D';
}

void printPart2SimilarityTable(const std::vector<std::string>& strings,
                               const std::vector<std::vector<int>>& lcs_table) {
    const std::size_t n = strings.size();
    // column width for 01 style labels and h m l d cells
    const int labW = 3;

    auto fmtIndex = [](std::size_t oneBased) {
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << oneBased;
        return oss.str();
    };

    std::cout << "\nSimilarity table (upper triangle: H/M/L/D per specification):\n";
    std::cout << std::string(static_cast<std::size_t>(labW * 2), ' ');
    for (std::size_t j = 0; j < n; ++j) {
        std::cout << std::setw(labW) << std::right << std::setfill(' ') << fmtIndex(j + 1);
    }
    std::cout << "\n";
    for (std::size_t i = 0; i < n; ++i) {
        std::cout << std::setw(labW) << std::right << std::setfill(' ') << fmtIndex(i + 1);
        std::cout << std::string(static_cast<std::size_t>(labW), ' ');
        for (std::size_t j = 0; j < n; ++j) {
            if (j < i) {
                std::cout << std::string(static_cast<std::size_t>(labW), ' ');
            } else if (j == i) {
                std::cout << std::setw(labW) << std::right << "-";
            } else {
                const int len = lcs_table[i][j];
                const char label = classifySimilarity(strings[i], strings[j], len);
                std::cout << std::setw(labW) << std::right << label;
            }
        }
        std::cout << "\n";
    }
}
