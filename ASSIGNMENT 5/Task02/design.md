# Task 02 — Part B1: Polymorphic billing implementation

The executable implements four concrete bills (outpatient, inpatient, day-care and emergency) and four payers (self-pay, insurance, government scheme and the extension CorporateTieUp). Every bill is held as unique_ptr<Bill> and every payer as unique_ptr<Payer>. The nested processing loop demonstrates run-time dispatch for every bill/payer combination.

## Hand-checkable bill totals
- OP Ravi: 500 + 1,200 = 1,700
- IP Meena: 3 × 2,500 + 40,000 = 47,500
- Day-care Asha: package = 22,000
- Emergency Imran: 1,500 + 30 × 100 = 4,500
- Daily total = 75,700

Insurance policy is a 50,000 limit with 20% co-payment: covered = min(total, limit) × 0.8. Government values are fixed package caps in the source. CorporateTieUp pays 70% up to 25,000.

## Validation plan
1. Check each bill total by hand using the table above.
2. Run all four payer policies against all four bills.
3. Remove virtual from Bill::total() and compile: the compiler rejects Bill as abstract/derived overrides no longer override the pure virtual signature; a non-pure non-virtual base method would instead statically bind to the base implementation.
4. Remove virtual from the base destructor only in a separate experimental copy. Deleting derived objects through Bill* is undefined behaviour; run that copy under AddressSanitizer and record the actual diagnostic.
5. Compare output with the A1 hierarchy. The implementation adds validated constructors and smart-pointer ownership; the public abstraction is unchanged.

## Template alternative
Use separate containers such as vector<OutPatientBill> and vector<InPatientBill>, with templated total-processing functions. Each item avoids a virtual dispatch call, but the types cannot naturally coexist in one homogeneous vector without a variant/type-erasure wrapper. Each container remains O(n) to process and stores only its concrete type. The polymorphic collection allows a single heterogeneous list and O(1) dispatch per item.