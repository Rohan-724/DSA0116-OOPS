# Task 01 — Part A: Polymorphic design and exception strategy

## A1. Common Bill interface and hierarchy

Every bill exposes `total() const`, `type() const`, and `print() const`. Common state: patient identifier/name and a unique bill identifier. Charges and bill-specific data belong in derived classes.

```text
                    Bill (abstract)
          patientId, patientName, billId
          + total() const = 0  [pure virtual]
          + type() const = 0   [pure virtual]
          + print() const     [ordinary virtual-independent helper]
          + virtual ~Bill()
             /       |         |          \
 OutPatientBill InPatientBill DayCareBill EmergencyBill
```

Each concrete class overrides total() and type(). Bill's virtual destructor ensures derived destructors execute when deleting through Bill*.

### SIMATS-style pseudocode: total for the day
```text
ALGORITHM CalculateDailyTotal
INPUT: Bills[0..n-1] as pointers to Bill
OUTPUT: dailyTotal
BEGIN
    dailyTotal <- 0
    FOR i <- 0 TO n-1 DO
        IF Bills[i] = NULL THEN
            CONTINUE
        END IF
        dailyTotal <- dailyTotal + Bills[i].total()
    END FOR
    RETURN dailyTotal
END
```

### Alternative: one structure plus type/switch
A Bill record would contain a type tag and a union/variant-like set of fields. total() switches on the tag. Both designs process n bills in O(n) time. A tagged record reserves storage for the largest bill-field set in every record; a class hierarchy stores only each concrete type's fields plus object dispatch overhead (commonly a vptr). Adding a type requires a new derived class and no changes to existing polymorphic processing; a switch requires editing and retesting the switch and its data representation.

## A2. Runtime binding, vtables and destructor

**Early binding:** a non-virtual call is selected from the static type at compile time. **Late binding:** a virtual call through Bill* uses the object's dynamic type, so `b->total()` dispatches to the concrete bill's override. The non-virtual `show()` example still calls OPBill::total() because total() itself is virtual.

Conceptual vtables (implementation detail; exact layout is compiler/ABI-specific):

| Bill vtable slot | Bill | OPBill | IPBill |
|---|---|---|---|
| destructor | Bill destructor | OPBill destructor | IPBill destructor |
| total() | pure-virtual entry | OPBill::total | IPBill::total |

A Bill object carries an implementation-managed vptr. At `b->total()`, the program loads the vptr, selects the total slot and invokes the function for the dynamic type. Removing virtual from the base destructor makes deletion of a derived object through Bill* undefined behaviour. It can skip derived cleanup and leak resources.

Alternative using dynamic_cast: test each of k known derived types until one matches, then call its total(). Worst-case O(k) type checks per bill (and O(nk) overall) rather than one virtual dispatch per bill. A vptr typically costs one pointer per polymorphic object; exact layout is implementation-specific.

## A3. Payer abstraction and extension

```text
Payer (abstract): amountCovered(const Bill&) = 0
  |-- SelfPay: returns full bill total
  |-- Insurance: coverLimit, coPaymentPercent
  |-- GovernmentScheme: fixed package rates by bill type
  |-- CorporateTieUp (new extension): negotiated percentage/limit
```

A new payer derives from Payer and implements amountCovered; the bill hierarchy and billing loop remain unchanged. A policy function or std::function is an alternative: both approaches are O(1) per policy call. A Payer object stores its policy state naturally in data members; a callable may capture state in its closure, whose size/representation is implementation-dependent.

## A4. Exception strategy

| Failure | Exception |
|---|---|
| Negative charge/invalid days | std::invalid_argument or BillingError |
| Claim exceeds cover | ClaimError |
| Unknown government package | PackageError |
| Missing patient record | PatientNotFound |
| Allocation failure | std::bad_alloc |
| Malformed numeric input | std::invalid_argument / std::out_of_range |

Hierarchy: std::exception -> std::runtime_error -> BillingError -> ClaimError, PackageError, PatientNotFound. Functions that validate, parse, allocate, construct bills or approve claims may throw. Simple accessors and destructors should be noexcept; destructors must not throw because a second exception during stack unwinding calls std::terminate.

Return-code alternative: return Status plus an output value/error message. It has predictable normal-path control flow but forces every caller to inspect and propagate status, and requires a place to store the error. Exceptions usually have little normal-path cost but are more expensive when thrown/caught; the error path unwinds the stack and searches for a handler.

## A5. Recovery, rethrowing and RAII

Catch close to the layer that can add useful context or recover. A service layer may log and use `throw;` to rethrow the same exception; the application boundary catches std::exception and reports a safe message. Use catch(...) only at a top-level boundary or cleanup boundary where unknown exceptions must not escape.

Stack unwinding destroys automatic objects in reverse construction order. std::vector, std::string, std::unique_ptr and file streams release their resources in destructors. Manual delete in every catch path duplicates cleanup and creates leak opportunities whenever a new error path is added. RAII has the same asymptotic cleanup cost and substantially reduces error-prone branching.

### Required output predictions (write before local execution)
- A2 snippet: `500 ~OPBill ~Bill` followed by newline. show() invokes virtual total(); delete through Bill* invokes derived then base destructor.
- A5 Guard snippet: `~f ~main caught 42` followed by newline. f's local Guard is destroyed during unwinding, then main's Guard; the statement after f() is skipped.

### Rethrow distinction
`throw;` rethrows the currently handled exception preserving its dynamic type and exception object. `throw e;` throws a new exception object whose type is the static type of e (potentially slicing a derived exception).