# Task 04 — Part B3: Runtime dispatch, switch, variant and exception cost

The benchmark compares three representations of the same generated bills:
1. virtual functions through a base-class pointer,
2. a tagged record and switch,
3. std::variant and std::visit.

For each data size (10, 1,000, 1,000,000 and 10,000,000), all three compute a checksum. Matching checksums validate equivalent results before comparing timing. It also measures 1,000,000 claims at 0%, 1% and 50% invalid rates using a return-code branch and thrown/caught invalid_argument.

## Run
```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic benchmark.cpp -o benchmark
./benchmark
```
Use the same machine, compiler and flags for repeated trials. Run at least five times; report median timings and record CPU/compiler details. Do not compare results from different build flags.

## Complexity and storage
- Virtual, switch and variant processing: O(n) total; O(1) processing work per bill. Virtual objects commonly carry a vptr and require indirect dispatch; the sample also uses one heap allocation per polymorphic object. Tagged records reserve fields for all cases. A variant element stores the largest alternative plus a discriminator/tag, with alignment padding. std::visit generally dispatches without a heap allocation per element.
- Claim validation: O(n) total and O(1) per claim for both return codes and exceptions. Exception cost depends strongly on how often errors are thrown; normal success paths and frequent error paths should be measured separately.
- The benchmark intentionally measures allocation/build separately from the iteration timer for the three dispatch strategies.

## Interpretation prompts
Use the actual results to explain whether indirect dispatch, branch prediction, allocation/locality and exception frequency dominate on your platform. Do not assume one design is always fastest. Virtual functions are attractive for open-ended extension and heterogeneous collections; switch is simple for a closed set; variant is useful for a closed set with value semantics and a single container.

## Results table (fill with your measurements)
| N / invalid rate | Virtual seconds | Switch seconds | Variant seconds | Return-code seconds | Exception seconds |
|---|---:|---:|---:|---:|---:|
| 10 | | | | — | — |
| 1,000 | | | | — | — |
| 1,000,000 | | | | 0% / 1% / 50% | 0% / 1% / 50% |
| 10,000,000 | | | | — | — |

The source prints measured seconds and checksums when executed. No timing results are claimed in this repository until the benchmark is run on the student's machine.