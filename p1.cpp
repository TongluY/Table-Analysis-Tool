// tooling and basics

#include "sparrow.h"
#include <iostream>

int main()
{
    std::bitset<32> a("11100000000001100000000000100010");
    std::bitset<32> b("01110000000001111000000000100001");

    auto bitsets = sparrow::warmup::BitAnd({a}, {b});
    if (bitsets.second)
    {
        std::cout << sparrow::warmup::CountBits(bitsets.first) << std::endl;
    }
    else
    {
        std::cerr << "BitAnd operation failed due to unequal vector sizes." << std::endl;
    }

    return 0;
}