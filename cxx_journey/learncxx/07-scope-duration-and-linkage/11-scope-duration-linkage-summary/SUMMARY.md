# Conclustion

## Scope

In general scope it is a zone where variable is visiable. Variables and functions in local scope are visible from the point of declarationstill the end of block.
- variables in local scope
- function parameters
- user-defined types inside block

Global variables and function are accessible from the point of declaration and till the end of programm.
Variables with same name as variable in outer block can hide or shadowing variable defined in outer block.
- global variables
- functions
- user-defined types in in global scope

## Duration

Duration sepecifiy variable time creation and destroying.

- automatic - from point of declaration til the end of block (destroyed automaticaly)
    - local variables
    - functions parameters
- static - from the start programm till the end of programm
    - global variables
    - static local variables
- dynamic - user detern where they are created and destroyed
    - dynamic allocated variables

## Linkage

Linkage detern where the two same names are refered to the one definition or not.

- no-linkage
    - local variables
    - user-defined types inside block
- internal linkage - can be accessible within one file where they declared
    - static function
    - static blobal variables
    - const global variables
    - function declared inside unnamed namespace
    - user-definded types declared inside unnamed namespace
- external lingage - can be accessible out of one file (via a forwrad declaration). `constexpr` variables can be `external` as the should be initialized in compile-time.
    - functions
    - non-const global variables
    - extern const global variables
    - inline const global variables

