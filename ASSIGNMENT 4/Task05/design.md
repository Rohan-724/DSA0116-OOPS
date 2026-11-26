# Task 5 — Pointers to objects and this

## Four access forms
- Direct object: Cart c; c.total(); automatic lifetime.
- Pointer to an existing object: Cart* p=&c; p->total(); non-owning, must not outlive c.
- Reference: Cart& r=c; r.total(); alias that must be initialised.
- Dynamic object: Cart* p=new Cart; ... delete p; explicit lifetime; prefer smart pointers in production.

this is a pointer to the current object inside a non-static member function. *this denotes that object as an lvalue. Returning Cart& enables chaining without a copy. this->discount distinguishes the data member from the parameter.

## Highest cart
The program scans an array of non-owning Cart pointers once: O(n) time and O(1) extra space.

## Returning Cart by value
Each call returns a copy. Chained calls may modify temporary copies instead of the original object, and copying the arrays/strings adds work. Returning Cart& operates on and returns the same object.

## vector<Cart> alternative
A vector stores objects directly and avoids a pointer indirection. Finding the maximum remains O(n). Vector growth can move elements and invalidate pointers, references and iterators to its elements; reserve capacity or avoid retaining such addresses across growth.