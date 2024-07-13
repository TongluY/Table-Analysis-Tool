#ifndef SPARROW_H
#define SPARROW_H

#include <bitset>
#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <cstdlib>
#include <memory>

namespace sparrow
{
    // p1
    namespace warmup
    {
        unsigned CountBits(std::bitset<32> bits, unsigned pos, unsigned len);
        unsigned CountBits(std::vector<std::bitset<32>> bitsets);
        std::pair<std::vector<std::bitset<32>>, bool> BitAnd(std::vector<std::bitset<32>> a,
                                                             std::vector<std::bitset<32>> b);
    }
    // p2
    struct NullableInts
    {
        std::vector<int> nums;
        std::vector<std::bitset<32>> valid;
    };

    struct AverageResult
    {
        double value;
        bool ok;
    };

    struct DivideResult
    {
        NullableInts value;
        bool ok;
    };

    void DropZero(NullableInts *nints);
    AverageResult Average(const NullableInts *nints);
    DivideResult Divide(const NullableInts *nints1, const NullableInts *nints2);

    // p3
    AverageResult Average(const NullableInts &nints);
    NullableInts *StrsToNullableInts(std::vector<std::string> inputs);
    int NullableIntsToArray(const NullableInts &nints, int **arr);

    // p4
    class IntColumn
    {
    private:
        std::vector<int> nums;
        std::vector<bool> valid; // Simplify the valid flags to a vector of bool for easier management.

    public:
        IntColumn();                                       // Default constructor
        IntColumn(const std::vector<std::string> &inputs); // Constructor to initialize from string vector
        void DropZero();
        AverageResult Average() const;
        IntColumn operator/(const IntColumn &other) const;
        int Size() const;
        const int *operator[](int idx) const; // Implement index operator for accessing elements

        friend std::ostream &operator<<(std::ostream &os, const IntColumn &column); // For printing
    };
    // p5
    class NamedIntColumn
    {
    public:
        std::string name = "";
        IntColumn *col = nullptr;

        NamedIntColumn(const std::string &name, const std::vector<std::string> &inputs);
        NamedIntColumn(const NamedIntColumn &other);
        NamedIntColumn(NamedIntColumn &&other);
        NamedIntColumn &operator=(const NamedIntColumn &other);
        NamedIntColumn &operator=(NamedIntColumn &&other);
        ~NamedIntColumn();

        // Overloads for division
        NamedIntColumn operator/(const NamedIntColumn &other) const;
        NamedIntColumn operator/(int divisor) const;
    };
    // p6
    class Table
    {
    private:
        std::vector<std::shared_ptr<NamedIntColumn>> columns;

    public:
        Table();
        Table(const std::string &filePath); // Constructor to load from file
        void AddCol(const NamedIntColumn &col);
        void AddCol(std::shared_ptr<NamedIntColumn> col);
        std::shared_ptr<NamedIntColumn> operator[](const std::string &colName) const;
        friend std::ostream &operator<<(std::ostream &os, const Table &table);
    };

}

#endif