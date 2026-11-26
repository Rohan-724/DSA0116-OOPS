# Task 3 — Constructors in derived and member classes

## Complete-code constructor
Student(const std::string& n, int a, long long r, const std::string& city, int pin)
: Person(n,a), regNo(r), home(city,pin) {}

This initialises the base and member objects in the member-initializer list.

## Construction and destruction rules
1. Virtual bases are constructed first, by the most-derived class.
2. Direct non-virtual bases follow base-specifier order.
3. Members are constructed in declaration order, not initializer-list order.
4. The constructor body runs last.
5. Destruction reverses completed construction: derived destructor body, members in reverse order, then bases in reverse order.

The program traces Address, Course, Person, Student, Staff and TeachingAssistant. Person is a virtual base of Student and Staff, so TeachingAssistant initialises one shared Person subobject.

## Removing virtual inheritance
Removing virtual from Student and Staff creates two Person subobjects in TeachingAssistant. Person fields become ambiguous. Record sizeof with and without virtual inheritance on your compiler; exact sizes depend on ABI and padding.

## Address pointer alternative
With Address*, the constructor must allocate, the destructor must delete, and copying must deep-copy or use deliberate smart-pointer semantics. The pointer adds pointer storage and a separate allocation. A direct Address member avoids that ownership complexity and usually improves locality.