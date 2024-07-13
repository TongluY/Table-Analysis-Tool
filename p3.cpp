// references and conversions

#include "sparrow.h"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
    using namespace std;
    // std::vector<std::string> inputs(argv + 1, argv + argc);
    vector<string> inputs;
    for(int i =1; i<argc;i++){
        inputs.push_back(argv[i]);
    }
    
    sparrow::NullableInts* nints = sparrow::StrsToNullableInts(inputs);

    sparrow::AverageResult result = sparrow::Average(*nints);

    if (!result.ok) {
        std::cout << "failed" << std::endl;
    }
    else {
        std::cout << result.value << std::endl;
    }

    delete nints;

    return 0;
}
