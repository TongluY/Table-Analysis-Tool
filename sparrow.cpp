#include "sparrow.h"
#include <bitset>
#include <vector>
#include <utility>
#include <iostream>
#include <utility>
#include <fstream>
#include <sstream>
using namespace std;

namespace sparrow
{
    // p1
    namespace warmup
    {
        unsigned CountBits(std::bitset<32> bits, unsigned pos, unsigned len)
        {
            if (pos + len > 32)
                len = 32 - pos;
            unsigned count = 0;
            for (unsigned i = pos; i < pos + len; ++i)
            {
                if (bits[i])
                    ++count;
            }
            return count;
        }

        unsigned CountBits(std::vector<std::bitset<32>> bitsets)
        {
            unsigned count = 0;
            for (const auto bits : bitsets)
            {
                count += bits.count();
            }
            return count;
        }

        std::pair<std::vector<std::bitset<32>>, bool> BitAnd(std::vector<std::bitset<32>> a,
                                                             std::vector<std::bitset<32>> b)
        {
            std::pair<std::vector<std::bitset<32>>, bool> result;
            if (a.size() != b.size())
            {
                result.second = false;
                return result;
            }

            result.second = true;
            for (size_t i = 0; i < a.size(); ++i)
            {
                result.first.push_back(a[i] & b[i]);
            }
            return result;
        }

    }
    // p2

    void DropZero(NullableInts *nints)
    {
        for (size_t i = 0; i < nints->nums.size(); ++i)
        {
            if (nints->nums[i] == 0 && nints->valid[i / 32][i % 32])
            {
                nints->valid[i / 32].reset(i % 32);
            }
        }
    }
    DivideResult Divide(const NullableInts *nints1, const NullableInts *nints2)
    {

        DivideResult result;
        if (nints1->nums.size() != nints2->nums.size())
        {
            result.ok = false;
            return result;
        }
        result.ok = true;

        result.value.nums.resize(nints1->nums.size(), 0);
        int requiredBitsets = (nints1->nums.size() + 31) / 32;
        result.value.valid.resize(requiredBitsets, std::bitset<32>(0));

        for (size_t i = 0; i < nints1->nums.size(); ++i)
        {
            if (nints1->valid[i / 32][i % 32] && nints2->valid[i / 32][i % 32] && nints2->nums[i] != 0)
            {
                result.value.nums[i] = nints1->nums[i] / nints2->nums[i];
                result.value.valid[i / 32].set(i % 32);
            }
        }

        return result;
    }
    AverageResult Average(const NullableInts *nints)
    {
        AverageResult result;
        if (nints == nullptr)
        {
            return {0.0f, false};
        }
        double sum = 0.0;
        int count = 0;

        for (size_t i = 0; i < nints->nums.size(); ++i)
        {
            if (nints->valid[i / 32][i % 32])
            {
                sum += nints->nums[i];
                count++;
            }
        }

        if (count > 0)
        {
            result.value = sum / count;
            result.ok = true;
        }
        else
        {
            result.value = 0.0;
            result.ok = false;
        }

        return result;
    }

    // p3
    AverageResult Average(const NullableInts &nints)
    {
        return Average(const_cast<NullableInts *>(&nints));
    }
    NullableInts *StrsToNullableInts(std::vector<std::string> inputs)
    {
        NullableInts *nullableInts = new NullableInts;

        size_t numBitsets = (inputs.size() + 31) / 32;
        nullableInts->valid.resize(numBitsets, std::bitset<32>());

        for (size_t i = 0; i < inputs.size(); ++i)
        {
            if (inputs[i] == "null")
            {
                nullableInts->nums.push_back(0);
                nullableInts->valid[i / 32][i % 32] = 0;
            }
            else
            {
                nullableInts->nums.push_back(std::stoi(inputs[i]));
                nullableInts->valid[i / 32].set(i % 32);
            }
        }

        return nullableInts;
    }
    int NullableIntsToArray(const NullableInts &nints, int **arr)

    {
        int count = 0;
        for (size_t i = 0; i < nints.nums.size(); ++i)
        {
            if (nints.valid[i / 32][i % 32])
            {
                ++count;
            }
        }
        *arr = new int[count];

        int j = 0;
        for (size_t i = 0; i < nints.nums.size(); ++i)
        {
            if (nints.valid[i / 32][i % 32])
            {
                (*arr)[j] = nints.nums[i];
                ++j;
            }
        }
        return count;
    }

    // p4
    IntColumn::IntColumn() {}

    IntColumn::IntColumn(const std::vector<std::string> &inputs)
    {
        for (const auto &str : inputs)
        {
            if (str == "null")
            {
                nums.push_back(0);
                valid.push_back(false);
            }
            else
            {
                nums.push_back(std::stoi(str));
                valid.push_back(true);
            }
        }
    }

    void IntColumn::DropZero()
    {
        for (size_t i = 0; i < nums.size(); ++i)
        {
            if (nums[i] == 0)
                valid[i] = false;
        }
    }

    AverageResult IntColumn::Average() const
    {
        double sum = 0;
        int count = 0;
        for (size_t i = 0; i < nums.size(); ++i)
        {
            if (valid[i])
            {
                sum += nums[i];
                ++count;
            }
        }
        return {count > 0 ? sum / count : 0, count > 0};
    }

    IntColumn IntColumn::operator/(const IntColumn &other) const
    {
        IntColumn result;
        size_t size = std::min(nums.size(), other.nums.size());
        result.nums.resize(size);
        result.valid.resize(size, false);

        for (size_t i = 0; i < size; ++i)
        {
            if (valid[i] && other.valid[i] && other.nums[i] != 0)
            {
                result.nums[i] = nums[i] / other.nums[i];
                result.valid[i] = true;
            }
        }
        return result;
    }

    int IntColumn::Size() const
    {
        return nums.size();
    }

    const int *IntColumn::operator[](int idx) const
    {
        if (idx < 0)
            idx += nums.size();
        if (idx >= 0 && idx < static_cast<int>(nums.size()) && valid[idx])
        {
            return &nums[idx];
        }
        return nullptr;
    }

    std::ostream &operator<<(std::ostream &os, const IntColumn &column)
    {
        os << "IntColumn:\n";
        for (size_t i = 0; i < column.nums.size(); ++i)
        {
            if (column.valid[i])
            {
                os << column.nums[i] << '\n';
            }
            else
            {
                os << "null\n";
            }
        }
        return os;
    }

    // p5
    NamedIntColumn::NamedIntColumn(const std::string &name, const std::vector<std::string> &inputs)
        : name(name), col(new IntColumn(inputs)) {}

    NamedIntColumn::NamedIntColumn(const NamedIntColumn &other)
        : name(other.name), col(new IntColumn(*other.col)) {}

    NamedIntColumn::NamedIntColumn(NamedIntColumn &&other)
        : name(std::move(other.name)), col(other.col)
    {
        other.col = nullptr;
    }

    NamedIntColumn &NamedIntColumn::operator=(const NamedIntColumn &other)
    {
        if (this != &other)
        {
            name = other.name;
            delete col;
            col = new IntColumn(*other.col);
        }
        return *this;
    }

    NamedIntColumn &NamedIntColumn::operator=(NamedIntColumn &&other)
    {
        if (this != &other)
        {
            name = std::move(other.name);
            delete col;
            col = other.col;
            other.col = nullptr;
        }
        return *this;
    }

    NamedIntColumn NamedIntColumn::operator/(const NamedIntColumn &other) const // p6
    {
        if (this->col == nullptr || other.col == nullptr)
        {
            throw std::runtime_error("One of the columns is uninitialized.");
        }
        if (this->col->Size() != other.col->Size())
        {
            throw std::runtime_error("Column sizes do not match.");
        }
        std::vector<std::string> results;
        for (int i = 0; i < this->col->Size(); ++i)
        {
            if ((*this->col)[i] && (*other.col)[i] && *(*other.col)[i] != 0)
            {
                int result = *(*this->col)[i] / *(*other.col)[i];
                results.push_back(std::to_string(result));
            }
            else
            {
                results.push_back("null"); // Handle null or zero division as needed
            }
        }
        return NamedIntColumn(this->name + "/" + other.name, results);
    }

    NamedIntColumn NamedIntColumn::operator/(int divisor) const // p6
    {
        if (this->col == nullptr)
        {
            throw std::runtime_error("The column is uninitialized.");
        }
        if (divisor == 0)
        {
            throw std::runtime_error("Division by zero.");
        }
        std::vector<std::string> results;
        for (int i = 0; i < this->col->Size(); ++i)
        {
            if ((*this->col)[i])
            {
                int result = *(*this->col)[i] / divisor;
                results.push_back(std::to_string(result));
            }
            else
            {
                results.push_back("null");
            }
        }
        return NamedIntColumn(this->name + "/" + std::to_string(divisor), results);
    }

    NamedIntColumn::~NamedIntColumn()
    {
        delete col;
    }
    // p6
    Table::Table() {}

    // Constructor to load from a file
    Table::Table(const std::string &filePath)
    {
        std::ifstream file(filePath);
        int numRows, numCols;
        file >> numRows >> numCols;
        std::string colName, value;
        std::vector<std::vector<std::string>> data(numCols);

        for (int i = 0; i < numCols; i++)
        {
            file >> colName;
            data[i].push_back(colName);
            for (int j = 0; j < numRows; j++)
            {
                file >> value;
                data[i].push_back(value);
            }
            AddCol(std::make_shared<NamedIntColumn>(data[i][0], std::vector<std::string>(data[i].begin() + 1, data[i].end())));
        }
    }

    void Table::AddCol(const NamedIntColumn &col)
    {
        columns.push_back(std::make_shared<NamedIntColumn>(col));
    }

    void Table::AddCol(std::shared_ptr<NamedIntColumn> col)
    {
        columns.push_back(col);
    }

    std::shared_ptr<NamedIntColumn> Table::operator[](const std::string &colName) const
    {
        for (const auto &col : columns)
        {
            if (col->name == colName)
                return col;
        }
        return nullptr; 
    }

    std::ostream &operator<<(std::ostream &os, const Table &table)
    {
        if (!table.columns.empty())
        {
            // Print column names
            for (size_t i = 0; i < table.columns.size(); i++)
            {
                os << table.columns[i]->name;
                if (i < table.columns.size() - 1)
                    os << ",";
            }
            os << "\n";

            // Print rows
            int numRows = table.columns[0]->col->Size(); // Assume all columns are the same size
            for (int i = 0; i < numRows; i++)
            {
                for (size_t j = 0; j < table.columns.size(); j++)
                {
                    const int *value = (*table.columns[j]->col)[i];
                    if (value)
                        os << *value;
                    else
                        os << "null";
                    if (j < table.columns.size() - 1)
                        os << ",";
                }
                os << "\n";
            }
        }
        return os;
    }
}