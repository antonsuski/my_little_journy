# Conclusion

When we use type deuction `auto` key word and initialize with rentrun reference value from function it will drop reference.

Here we shoul understand **top-level** and **low-level** `const` qualifier e.g.
```cpp
const int a { 123 }; // const here is top-level qualifier
int * const b { &a ]; // const here is top-level qualifier
```
```cpp
const int& c { a }; // const here is low-level qualifier
const int* d { a }; // const here is low-level qualifier
```
```cpp
const int * const { a }; // here we have both const level qualifier, left const is the low-level and right const is top-level
```

While type deduction it also drops **top-level** `const` qualifier.
While type deduction with pointer it woun't drop pointer, just a `const` qualifier could be droped.
If you want to prevent from dropping some qualifiers or types you can add it at declaration. e.g.
```cpp
// for refs
auto& ref1 { get_some_ref() };
const auto& ref2 { get_some_ref() };

// for pointers
const auto ptr1 { get_some_ptr() }; // remmeber that the ateriks doesn't drop it self while type deduction
auto * const ptr2 { get_some_ptr() };
```

