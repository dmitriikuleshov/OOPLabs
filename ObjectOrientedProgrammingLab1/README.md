# ObjectiveOrientedProgramming (LabWork 1)

## ***Variant 10***

Write a function that returns a string, where each element represents one bit of a 32-bit integer such that when printed, it looks like the binary representation of the integer (with the least significant bit on the right).
For example, 1 = `00000000000000000000000000000001`.
Assign each element of the array to either 1 or 0 depending on whether the bit in the corresponding position is 1 or 0.

### Example (input -> output):
- `1` -> `[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1]`

The function takes one argument `(n)`, which is a positive integer to be converted into binary format.


## Objective:
- Study the CMake build system
- Study the basic operators and constructs of C++
- Study the library for writing unit tests, Google Test
- Learn to write simple programs using input/output through streams `std::cin` and `std::cout`

## Workflow:
1. Familiarize yourself with the theoretical material.
2. Obtain your assignment variant from the instructor.
3. Implement the assignment for your variant according to the given requirements.
4. Write unit tests using Google Test.
5. Create a repository on GitHub.
6. Upload the lab files to the repository.
7. Report on the completed work by demonstrating the working program on test data sets (both self-prepared and those suggested by the instructor) and answering the instructor's questions (both control questions and questions about the program's implementation).

## Program Requirements:
- Develop a program in C++ according to the assigned variant.
- The C++ program must be built using the CMake build system.
- The program must compile using the GCC 14 compiler.
- The program must take input from standard input (`std::cin`) and output data to standard output (`std::cout`).
- It is necessary to register on GitHub and create a repository for the lab assignments.
- The instructor should be provided with a link to the public repository on GitHub, a demonstration of the program's functionality, and answers to theoretical questions related to the topic of the lab assignment.


### Run project using cmake 

```bash
cmake -S . -B build && cmake --build build
# -S <path-to-source>          = Explicitly specify a source directory.
# -B <path-to-build>           = Explicitly specify a build directory.
# --build <dir>                = Build a CMake-generated project binary tree.
```
