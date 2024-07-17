## Project Overview

Welcome to Sparrow! Inspired by Apache Arrow and Python's pandas library, I developed Sparrow as a protocol and library designed for efficient table analysis. Sparrow aims to address some of the limitations of pandas, offering improved speed and support across multiple programming languages, including C++.

### Key Improvements Over pandas

While pandas is a powerful tool for data analysis, it has certain limitations that Sparrow aims to overcome:

1. **Performance**: pandas can be slow when handling large datasets due to its row-based storage format. Sparrow uses a columnar storage format, similar to Arrow, which allows for faster data processing and retrieval.
  
2. **Memory Usage**: pandas may consume significant memory, especially with large datasets. Sparrow's columnar format optimizes memory usage, making it more efficient for handling big data.

3. **Multi-Language Support**: pandas is primarily a Python library, limiting its use in applications written in other languages. Sparrow, inspired by Arrow, is designed to be used in multiple programming languages, including C++, providing greater flexibility for integration into diverse projects.

4. **Missing Data Handling**: In pandas, handling missing data, especially for integer columns, can be cumbersome. Sparrow offers a more streamlined approach to represent missing integers, similar to how NaN is used for floats.

### 6 Stages of the Project:
**P1: Tooling and Basics**
Create a shared library and a simple program that manipulates bits of data using tools like a compiler and make. Implement functions to count bits and perform bitwise operations.

**P2: NullableInts**
Develop an efficient way to represent integers with some missing values using vectors and bitsets. Implement functions to drop zero values, compute averages, and perform element-wise division.

**P3: References and Conversions**
Improve NullableInts functions by using references and const, and add conversion functions between NullableInts and other formats. Write a program that constructs a NullableInts based on command line arguments.

**P4: Class-Based Implementation**
Create an IntColumn class with functionality similar to NullableInts, leveraging object-oriented programming features. Implement methods for dropping zero values, computing averages, and performing element-wise division using operator overloading.

**P5: Copying and Moving**
Create a NamedIntColumn type with a string name and a pointer to an IntColumn object. Practice moving and copying by implementing constructors and assignment operators for the NamedIntColumn.

**P6: Table**
Create a Table type that manages a collection of NamedIntColumn objects using shared pointers. Implement methods for adding columns, retrieving columns by name, and performing file I/O to load and save table data.



The project is able to perform a variety of powerful table operations with Sparrow, such as:

- Extracting a column from the table:
  ```python
  t["c"]
  ```
- Adding the numbers in two columns without using a loop:
```
t["x"] + t["y"]
```
- Applying a function to every value in a column to produce a new column:
```
t["c"].apply(f)
```
- Creating a column of Booleans for values greater than a certain threshold:
```
t["c"] > 3
```
- Filtering the table to include only rows where a condition applies
```
t[t["c"] > 3]
```
Sparrow aims to enhance your table analysis capabilities, providing a more efficient and versatile toolset for your data processing needs. Let's get started!
