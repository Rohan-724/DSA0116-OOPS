# Task 1 — Class design review

## Diagnosis
1. Shared identity and pay fields are duplicated.
2. Public fields allow invalid or inconsistent state.
3. The same concepts have inconsistent names (name/nm and id/code).
4. The da field is unused.
5. 0.42 is a magic number.
6. Adding a staff category requires more duplicated code and changes to processing logic.
7. The three types cannot be processed uniformly through one polymorphic loop.

## Repaired hierarchy
Staff (abstract: name, id, basic pay, virtual pay())
- Professor: research allowance
- LabAssistant
- GuestFaculty: hours and hourly rate

Staff::pay() is pure virtual. Derived classes override it. A virtual destructor supports deletion through base pointers. The payroll uses a collection of base-class smart pointers and one loop.

## Design defence (under 100 words)
The hierarchy centralises shared identity and salary behaviour in Staff, while each derived class implements its own pay rule. Payroll code stores base-class pointers and calls pay() polymorphically, so adding another category requires a new derived class rather than editing a large switch statement or existing payroll loop. Private data protects object invariants, and the virtual destructor supports safe cleanup through base pointers.

## Alternative and complexity
A single Staff class would need a category field and a switch in pay(). Every new category changes that switch and often the class fields or constructors. Both designs take O(1) time per pay calculation. The single class reserves fields that may be unused for a particular category; the hierarchy stores category-specific fields only where needed.

## UML text
Staff (abstract) -> Professor, LabAssistant, GuestFaculty. Professor adds researchAllowance; GuestFaculty adds hours and hourlyRate.