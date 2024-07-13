// object oriented programming
#include "sparrow.h"
#include <iostream>
#include <vector>
#include <string>

using namespace sparrow;

int main(int argc, char* argv[]) {
    std::vector<std::string> inputs(argv + 1, argv + argc);

    IntColumn col(inputs);
    col.DropZero();
    std::cout << col;

    AverageResult avgResult = col.Average();
    if (avgResult.ok) {
        std::cout << "Avg: " << avgResult.value << std::endl;
    } else {
        std::cout << "Avg: failed" << std::endl;
    }

    return 0;
}
