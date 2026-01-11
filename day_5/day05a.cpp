#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../utils/utils.h"

struct Range {
    long start;
    long end;
};

static std::vector<Range> readAndMerge(std::ifstream& file,
                                       std::vector<long>& values)
{
    std::vector<Range> ranges;
    ranges.reserve(1024);
    values.reserve(1024);

    std::string line;
    bool reading_ranges = true;

    while (std::getline(file, line)) {
        if (line.empty()) {
            reading_ranges = false;
            continue;
        }

        if (reading_ranges) {
            long start, end;
            if (std::sscanf(line.c_str(), "%ld-%ld", &start, &end) == 2) {
                ranges.push_back({start, end});
            }
        } else {
            values.push_back(std::stol(line));
        }
    }
    if (ranges.empty()) {
        return {};
    }

    std::sort(ranges.begin(), ranges.end(),
              [](const Range& a, const Range& b) {
                return a.start < b.start;
              });
    
    std::vector<Range> merged;
    merged.reserve(ranges.size());

    merged.push_back(ranges.front());
    for (size_t i = 1; i < ranges.size(); ++i) {
        Range& last = merged.back();
        const Range& current = ranges[i];

        if (current.start > last.end + 1) {
            merged.push_back(current);
        } else {
            last.end = std::max(last.end, current.end);
        }
    }

    return merged;
}


static bool valueInRanges(long value, const std::vector<Range>& ranges)
{
    size_t left = 0;
    size_t right = ranges.size();

    while (left < right) {
        size_t mid = left + (right - left) / 2;
        const Range& r = ranges[mid];

        if (value < r.start) {
            right = mid;
        } else if (value > r.end) {
            left = mid + 1;
        } else {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[])
{

try {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);

        const std::string input = getInputPath(argc, argv, "day05_input");
        std::ifstream file = openFile(input);

        std::vector<long> values;
        std::vector<Range> ranges = readAndMerge(file, values);

        int count = 0;
        for (long v : values) {
            if (valueInRanges(v, ranges)) {
                ++count;
            }
        }

        std::cout << "Count = " << count << '\n';
        return 0;
    }

    catch (const std::exception& e) {
        std::cerr << "EXCEPTION: [" << e.what() << '\n';
        return 1;
    }
}