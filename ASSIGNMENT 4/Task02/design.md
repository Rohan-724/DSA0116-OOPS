# Task 2 — From requirement to hierarchy

## Relationships
- Student is-a Person: public virtual inheritance.
- Staff is-a Person: public virtual inheritance.
- TeachingAssistant is-a Student and Staff: public multiple inheritance.
- ResearchScholar is-a Student: public multilevel inheritance.
- Address, Course and similar owned data are has-a composition relationships.

This combines hierarchical, multiple, multilevel and hybrid inheritance.

## Diamond problem
Without virtual inheritance, TeachingAssistant contains two Person subobjects. Access to name becomes ambiguous and identity data is duplicated. Declaring Student and Staff as virtual public Person creates one shared Person subobject. The most-derived TeachingAssistant constructor initialises that virtual base directly.

## Person access table
| Person member | public inheritance | protected inheritance | private inheritance |
|---|---|---|---|
| public | public | protected | private |
| protected | protected | protected | private |
| private | inaccessible | inaccessible | inaccessible |

Public inheritance is used for substitutability. The example uses protected identity fields for derived-class access; a production design could use private fields and accessors.

## Composition alternative
TeachingAssistant could contain Student and Staff objects. That is has-a rather than is-a and may contain two Person identities unless one Person object is deliberately shared. It avoids inheritance ambiguity but does not make the TA substitutable for Student or Staff. Use sizeof on the target compiler to compare layouts; exact sizes are implementation-dependent.