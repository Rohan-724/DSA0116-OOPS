# Task 4 — Pointers to derived classes: forensics

## Defects
- rate() is non-virtual, so Account* calls the base implementation (3.5), even for SeniorAccount.
- The base destructor is non-virtual. Deleting a derived object through Account* is undefined behaviour; the derived destructor may not run and its array may not be released.
- Account copy = SeniorAccount() slices the object: only the Account base subobject is copied.
- Mark intended overrides with override.

## Repair
The program makes rate() virtual, gives Account a virtual destructor, and owns the history array with unique_ptr<double[]>. A vector of unique_ptr<Account> preserves dynamic types and cleans up automatically.

## Prediction exercise
The supplied snippet prints: 3.5 4 3.5
- p->rate() is statically bound to non-virtual Account::rate().
- p->vrate() dispatches at run time to SeniorAccount::vrate().
- copy.vrate() uses the sliced Account object, whose dynamic type is Account.

## Prevention rules
1. A polymorphic base should have a virtual destructor.
2. Mark overrides with override and prefer owning smart pointers over unmanaged owning raw pointers.

Run the original defective code and repaired code separately under AddressSanitizer; record actual diagnostics from your environment rather than assuming the result.