# C++ Programming Tasks

This repository contains solutions for 3 programming tasks demonstrating various C++ concepts and skills.

### Task 1: Search Engine Suggestions
Implementation of a search suggestion module for a search engine. The system should:
- Allow adding new search queries
- Return the most similar queries to user input (e.g., based on longest prefix match)

Example usage:
```
> add: When is New Year in China?
> add: When is New Year in Thailand?
> ask: When is New Year
result: When is New Year in China?
result: When is New Year in Thailand?
```

### Task 2: Triangle Collision Detection
Implementation of a 2D triangle collision detection system with visualization. Features:
- `isColliding` function that checks if two 2D triangles intersect
- Visual representation of triangles on screen
- User-controlled triangle movement
- Visual collision feedback

The collision detection works with the following structures:
```cpp
struct vec2 {
    float x, y;
};

struct triangle {
    std::array<vec2, 3> points;
};

bool isColliding(const triangle& triangle1, const triangle& triangle2);
```

### Task 3: Binary Operation Calculator
Implementation of a function that performs n-fold application of a binary operation on a value. The operation must satisfy certain mathematical properties and not have side effects.

The function signature:
```cpp
template <class T, class Op>
concept IsSupported = requires(T first, T second, Op operation) {
    { operation(first, second) } -> std::convertible_to<T>;
    { T::identity() } -> std::convertible_to<T>;
};

template <class BinaryOp, class ValueType>
requires IsSupported<ValueType, BinaryOp>
ValueType calculate(int n, ValueType value, const BinaryOp& f);
```

Properties that the binary operation `f` must satisfy:
- `f(x, T::identity()) == f(T::identity(), x) == x`
- `f(f(x, y), z) == f(x, f(y, z))`
- No side effects

Example: `calculate(3, x, f)` should be equivalent to `f(f(x, x), x)`

## Building and Running

### Prerequisites
- CMake 3.16 or higher
- C++20 compatible compiler

### Clone Instructions

Download the repository and initialize it's submodules
```bash
git clone --recursive https://github.com/tomtar00/cpp-tasks.git
```

### Build Instructions

Build the project using CMake:
```bash
cmake -B build
cmake --build build
```

### Running the Programs

After building, you can run each task's executable:

```bash
# Run Task 1
./build/task1

# Run Task 2
./build/task2

# Run Task 3  
./build/task3
```

### Running Tests

To run the test suite:

```bash
./build/tests
```

You can also run specific test cases using Catch2's command line options:

```bash
# Run tests for a specific task
./build/tests "[task1]"
./build/tests "[task2]"
./build/tests "[task3]"
```

## Dependencies

- [Catch2](https://github.com/catchorg/Catch2) - A modern C++ testing framework
- [SFML](https://github.com/SFML/SFML) - Simple and Fast Multimedia Library for graphics

## License

This project is under [MIT License](LICENSE)
