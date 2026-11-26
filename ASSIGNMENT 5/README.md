# Assignment 5 — Reliable Software with Runtime Polymorphism and Exceptions

**Student:** E. Rohan  
**Register number:** 192524482  
**Course:** DSA01 — C++  
**Repository:** [Rohan-724/DSA0116-OOPS](https://github.com/Rohan-724/DSA0116-OOPS)  
**Folder:** ASSIGNMENT 5  
**Language standard:** C++17

## Folder contents
- Task01 — Part A design: Bill/Payer hierarchies, UML-style diagram, vtables, pseudocode, exception taxonomy, recovery and complexity alternatives.
- Task02 — Part B1: complete polymorphic billing application with four bill types and four payers.
- Task03 — Part B2: claim approval TODOs, validation failures, rethrowing, RAII and allocation-failure probe.
- Task04 — Part B3: virtual vs switch vs variant benchmark and return-code vs exception benchmark.
- Task05 — Part B4: new MaternityBill and EmployerScheme extensions plus production decision.

Each task folder contains source code and/or design notes.

## Build and run
Compile each C++ file independently because it contains its own main():
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o task
./task
```
For address and undefined-behaviour sanitizers where supported:
```bash
g++ -std=c++17 -Wall -Wextra -pedantic -fsanitize=address,undefined -g main.cpp -o task
./task
```
Benchmark (optimised build):
```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic benchmark.cpp -o benchmark
./benchmark
```

## Required local evidence
- [ ] Record exact compiler and version using `g++ --version`.
- [ ] Compile and run each task; retain actual terminal screenshots.
- [ ] Write the A2, A5 and B2 output predictions before execution, then compare with actual output.
- [ ] Test negative charges, over-cover claims, unknown package, missing patient, malformed numeric input and allocation failure.
- [ ] Run the destructor experiment with virtual removed in a separate copy under AddressSanitizer.
- [ ] Run sanitizer builds for all relevant programs and retain actual reports.
- [ ] Run benchmark at 10, 1,000, 1,000,000 and 10,000,000 bills; repeat and report median.
- [ ] Benchmark one million claims at 0%, 1% and 50% invalid rates for both return codes and exceptions.
- [ ] Complete measured results, screenshots and the report cover page GitHub link.

**Evidence integrity:** This repository includes implementation, design analysis and reproducible benchmark code. It does not claim local compiler output, screenshots, measured timings or sanitizer results; those must be produced by executing the programs in your own environment.