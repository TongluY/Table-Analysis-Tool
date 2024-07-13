// structs and pointers

#include <iostream>
#include <vector>
#include <bitset>
#include "sparrow.h"

int main() {
    using namespace sparrow;

    NullableInts nints1{.nums={20,999,40,60}, .valid={std::bitset<32>("00000000000000000000000000001101")}};
    NullableInts nints2{.nums={10,10,0,20}, .valid={std::bitset<32>("00000000000000000000000000001111")}};

    DropZero(&nints2);

    DivideResult divResult = Divide(&nints1, &nints2);

    if (divResult.ok) {
        AverageResult avgResult = Average(&divResult.value);
        if (avgResult.ok) {
            std::cout << avgResult.value << std::endl;
        } else {
            std::cerr << "something wrong in average" << std::endl;
            return 1; 
        }
    } else {
        std::cerr << "something wrong in divide" << std::endl;
        return 1;
    }

    return 0; 
}
