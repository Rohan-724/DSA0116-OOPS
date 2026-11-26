# Assignment 3 — C++ Operator Overloading and Object Lifetime

**Student:** E. Rohan  
**Register number:** 192524482  
**Repository:** DSA0116-OOPS  
**Language standard:** C++17

## Task folders
- Task01 — Constructors and constructor overloading
- Task02 — Copy constructor, copy assignment and deep copying
- Task03 — Dynamic allocation, object lifetime and auditorium seat booking
- Task04 — Money arithmetic and stream operators
- Task05 — Prefix/postfix increment, comparisons and checked playlist indexing
- Task06 — Dynamic text class and operator overloading
- Task07 — Complex arithmetic and RLC impedance

## Build and run
Compile any task independently from its folder:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o task
./task
```

For memory checking on supported GCC/Clang systems:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -fsanitize=address,undefined -g main.cpp -o task
./task
```

Run one task at a time; each folder has its own `main.cpp`.

## Validation checklist
- [ ] Compile and run each task on the required compiler.
- [ ] Capture genuine terminal screenshots showing compilation and output for each task.
- [ ] Run sanitizer builds and record actual results.
- [ ] Add any required measured timings and compiler/version details.
- [ ] Review outputs against the assignment PDF before final submission.

**Evidence note:** Screenshots, measured timings, and sanitizer results are intentionally not fabricated. Add the actual results from your machine before submitting.
