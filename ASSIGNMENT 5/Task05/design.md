# Task 05 — Part B4: Final engineering decision

## Extensions
- New bill type: MaternityBill adds package and extras and overrides type()/total().
- New payer: EmployerScheme covers a configured percentage.
Neither extension changes Bill, existing bill classes, Payer or existing payer classes. The same polymorphic loops process them.

## Resource safety
All bill and payer objects are owned by std::unique_ptr in std::vector. Both abstract bases have virtual noexcept destructors. Validation failures throw standard exceptions; stack unwinding destroys vector elements and their owned objects. Run the complete program and exception tests under AddressSanitizer and attach the actual clean report/output from the local toolchain.

## Production decision
For 15 hospitals, two new bill types and three new payers per year, and 200,000 bills per day, the open polymorphic design is a sound maintainability choice: new concrete types implement stable interfaces without edits to the billing loop. O(n) billing work is expected; the dispatch cost is typically small relative to database, I/O, pricing and policy work, but the local benchmark should be used to validate that assumption. Exceptions suit exceptional validation/configuration failures; routine high-volume business rejections may be clearer and faster as explicit result/status values if measurements show frequent failures.

A production deployment additionally needs persistent transaction storage, audit trails, idempotent settlement, currency-safe decimal arithmetic, authentication/authorisation, concurrency controls, policy versioning and integration tests. Never rely on in-memory vectors as the durable billing ledger.

## Plug-in/configuration alternative
Load bill/payer rules from validated configuration. Rule interpretation costs depend on rule complexity; a precompiled/validated lookup can be O(1) per bill, while scanning rules may be O(r). Rule storage is O(r) for r configured policies. Plugins/configuration let operations change rates without recompilation but introduce schema/versioning, validation and configuration-security risks. C++ subclasses provide compile-time type checking and clearer behaviour but require a build/release to deploy a new class. A hybrid can load rates/configuration while retaining typed strategy interfaces.

## Evidence checklist
- [ ] Compile and run all task programs with the README commands.
- [ ] Add terminal output screenshots and test input files.
- [ ] Record compiler/version and OS/CPU.
- [ ] Run ASan/UBSan on billing and exception tests; retain actual report.
- [ ] Run benchmark at all required sizes and invalid rates; fill the results table with repeated medians.
- [ ] Record the before-run predictions and compare with observed output.
- [ ] Include the actual GitHub link in the report cover page.