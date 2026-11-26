# Assignment 4 — Designing Reusable Class Hierarchies

**Student:** E. Rohan  
**Register number:** 192524482  
**Course:** Object Oriented Programming with C++ (DSA01)  
**Repository:** DSA0116-OOPS  
**Folder:** ASSIGNMENT 4  
**Language standard:** C++17

## Contents
- Task01 — Payroll hierarchy, polymorphic pay and design review
- Task02 — University people hierarchy, hybrid inheritance and virtual-base diamond
- Task03 — Derived/member constructors and construction/destruction traces
- Task04 — Account polymorphism, virtual destructor, slicing and smart-pointer repair
- Task05 — Cart access forms, this pointer, chaining and highest-total search
- Task06 — Abstract vehicle hierarchy and extensible rental fleet

Each task folder contains main.cpp and design.md.

## Compile and run
From a task folder:
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o task
./task
```
For memory diagnostics where supported:
```bash
g++ -std=c++17 -Wall -Wextra -pedantic -fsanitize=address,undefined -g main.cpp -o task
./task
```
Compile each task separately because each source has its own main().

## Execution and evidence checklist
- [ ] Record actual compiler version using g++ --version.
- [ ] Compile and run all six task programs locally.
- [ ] Capture genuine terminal screenshots for compilation and output.
- [ ] Write required output predictions before running prediction programs, then compare with actual output.
- [ ] Run the original defective Account example and repaired example under AddressSanitizer; retain actual diagnostics.
- [ ] Perform requested experiments (sizeof comparisons, initializer-order warning, measurements and sanitizer evidence).
- [ ] Add measured results and report evidence required by the assignment PDF.

**Evidence integrity:** Source code and design notes are provided. Screenshots, measured timings, compiler output and sanitizer results are not fabricated; add these after personally executing the programs.
