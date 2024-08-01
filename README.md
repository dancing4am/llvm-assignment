# llvm-assignment

## Overview
This is an out-of-tree LLVM plugin example, that uses bogus conditional branch by command line argument `--bogus=<BOOLEAN>`.

## Development Environment
### Platform Support And Requirements

This project has been tested on **Ubuntu 22.04.4 LTS**.
In order to build **llvm-assignment** you will need:

- LLVM 18
- C++ compiler that supports C++17
- CMake 3.20 or higher

In order to run the passes, you will need:

- **clang-18** (to generate input LLVM files)
- [opt](https://llvm.org/docs/CommandGuide/opt.html) (to run the passes)

There are additional requirements for tests (these will be satisfied by installing LLVM 18):

- [lit](https://llvm.org/docs/CommandGuide/lit.html) (aka **llvm-lit**, LLVM tool for executing the tests)
- [FileCheck](https://llvm.org/docs/CommandGuide/FileCheck.html) (LIT requirement, it's used to check whether tests generate the expected output)


## Building & Testing

### Building
You can build **llvm-assignment** (and all the provided pass plugins) as follows:

```
cd <build/dir>
cmake -DLT_LLVM_INSTALL_DIR=<installation/dir/of/llvm/18> <source/dir/llvm/assignment>
make
```

The `LT_LLVM_INSTALL_DIR` variable should be set to the root of either the installation or build directory of LLVM 18. It is used to locate the corresponding `LLVMConfig.cmake` script that is used to set the include and library paths.

### Testing
In order to run **llvm-assignment** tests, you need to install **llvm-lit** (aka **lit**). It's not bundled with LLVM 18 packages, but you can install it with **pip**:
```
# Install lit - note that this installs lit globally
pip install lit
```
Running the tests is as simple as:
```
$ lit <build_dir>/test
```

## Running

### Generating Input

Before you can test it, you need to prepare an input file:
```
# Generate an LLVM test file
$LLVM_DIR/bin/clang -O1 -S -emit-llvm <source/dir/llvm/assignment>/inputs/input_for_obfuscator.cpp -o input_for_obfuscator.ll
```

### Generating Output

```
# Watch out '>' between input and output
$LLVM_DIR/bin/opt -load-pass-plugin <BUILD_DIR>/lib/libObfuscator.{so|dylib} --bogus=<BOOLEAN> -passes=obfuscator
-S <INPUT_LLVM_FILE> > <OUTPUT_LLVM_FILE>
```

### Without Output

```
$LLVM_DIR/bin/opt -load-pass-plugin <BUILD_DIR>/lib/libObfuscator.{so|dylib} --bogus=<BOOLEAN> -passes=obfuscator
-disable-output <INPUT_LLVM_FILE>
```

>Above description is mostly copied for convenience from [llvm-tutor README](https://github.com/banach-space/llvm-tutor?tab=readme-ov-file).



