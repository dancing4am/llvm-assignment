# llvm-assignment

## Development Environment
### Platform Support And Requirements

This project has been tested on **Ubuntu 22.04.4 LTS**.
In order to build llvm-assignment you will need:

- LLVM 18
- C++ compiler that supports C++17
- CMake 3.20 or higher

In order to run the passes, you will need:

- **clang-18** (to generate input LLVM files)
- [opt](https://llvm.org/docs/CommandGuide/opt.html) (to run the passes)

There are additional requirements for tests (these will be satisfied by installing LLVM 18):

- [lit](https://llvm.org/docs/CommandGuide/lit.html) (aka **llvm-lit**, LLVM tool for executing the tests)
- [FileCheck](https://llvm.org/docs/CommandGuide/FileCheck.html) (LIT requirement, it's used to check whether tests generate the expected output)


   
>Above description is copied for convenience from [llvm-tutor README](https://github.com/banach-space/llvm-tutor?tab=readme-ov-file).
