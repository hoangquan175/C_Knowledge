# C_Knowledge — C programming exercises and Linux assignment

`C_Knowledge` is a structured repository of C programming exercises, sample projects, and a Linux programming assignment. It is designed as a learning resource for practical C programming topics such as variables, control flow, pointers, arrays, structures, input/output, and low-level Linux utilities.

## Highlights
- Organized exercise projects under `Chapter1/` through `Chapter7/`.
- Each exercise typically includes a `Project/` folder with `src/`, `inc/`, `Makefile`, and example input files when applicable.
- Includes a dedicated Linux programming assignment in `LinuxProgrammingAssignment/Project`.
- Coding style guidance is available in `CODING_CONVENTION.md`.

## Repository layout
- `ChapterN/` — Chapter directories grouped by topic. Each chapter contains one or more `Project/` exercises.
- `ProjectSample/` — A reference project structure that demonstrates how exercise folders are organized.
- `LinuxProgrammingAssignment/Project` — A larger hands-on Linux programming assignment with input files and helper scripts.

## Short folder structure
- Part 1: `Chapter1/` through `Chapter7/`
  - Seven parts covering the fundamentals of C programming.
  - Topics are arranged in a progression similar to K&R, 2nd edition, with practical examples and exercises.
- Part 2: `LinuxProgrammingAssignment/Project`
  - A standalone Linux programming assignment containing source files, sample input, and build instructions.

## Build and run
Most exercises provide a `Makefile` in the `Project/` folder.

A typical workflow is:

```bash
cd Chapter7/LineInputandOutput/Project
make -f Makefile
./program.exe
```

Some programs read from standard input or accept file arguments. Common usage patterns include:

```bash
./program.exe < input.txt
./program.exe arg1 arg2
```

Review the source file in `src/` for exercise-specific behavior and command-line options.