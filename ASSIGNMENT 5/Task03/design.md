# Task 03 — Part B2: Error conditions, catch/rethrow and RAII

## Complete-the-code TODO answers
```cpp
double approve(double billed, double cover) {
    if (billed < 0 || cover < 0)
        throw std::invalid_argument("negative amount");
    if (billed > cover)
        throw ClaimError("exceeds cover");
    return billed;
}
// In settle's ClaimError handler:
std::cout << "audit: " << e.what() << '\\n';
throw;
```

Expected claim program output:
```text
approved 40000
audit: exceeds cover
claim rejected: exceeds cover
error: negative amount
```

Expected validation/rethrow output:
```text
ok done caught negative [log too large] caught too large
```
Only out_of_range is logged and rethrown because process() catches only out_of_range. invalid_argument is not matched there and propagates directly to main.

## Required failure tests
The executable covers negative amounts, claims above cover, malformed numeric text via stod, missing patient, and an intentionally impossible allocation request. The allocation test catches bad_alloc and also catches other standard exceptions because implementations may reject the request as bad_array_new_length (derived from bad_alloc) or another length-related failure. Run it separately if your OS uses memory overcommit; do not attempt huge allocations on a constrained production machine.

A top-level catch(const std::exception&) reports known standard failures; catch(...) can be added at the process boundary to keep an application from terminating on an unknown exception. A catch-all must not silently continue with corrupted state.

## Predict output before execution
- Guard snippet: `~f ~main caught 42`. Destruction during stack unwinding is reverse construction order. The output after f() is skipped because throw transfers control to a matching handler.
- validate/process snippet: `ok done caught negative caught too large` with the log inserted only for the too-large out_of_range: exact combined output is `ok done caught negative [log too large] caught too large`.

## Return-code alternative
Return Status (success, negative, over-cover) plus an output amount/error detail. Both approaches are O(1) per claim. Return codes do work on every path and require caller checks; exceptions typically keep the success path straightforward but have greater cost on thrown paths. std::optional<double> represents approved vs rejected but does not carry a reason; a richer expected/result type would carry an error. Result storage is O(1) per claim; optional adds a presence tag and aligned value storage.

## Million-claim experiment plan
Generate 1,000,000 deterministic claims at 0%, 1% and 50% invalid rates. Time return-code validation and exception-based validation separately using std::chrono, same data and compiler flags. Record actual timings in results.csv after running; do not treat predictions as measurements. Expected asymptotic time is O(n) for both, with the exception approach sensitive to invalid frequency.